/**
*********************************************************************
*********
* @project_name :micro_snow
* @file : touch.cpp
* @author : ruixuezhao890
* @brief : None
* @attention : None
* @date : 2024/12/30 
*********************************************************************
*********
*/
#include "device/touch/touch_device.h"
bool touch_device::touch_interrupts_= false;

bool touch_device::iic_read(uint8_t driver_addr, uint16_t reg_addr, uint8_t *reg_data, uint32_t length) {
    touch_wire->beginTransmission(driver_addr);
    touch_wire->write((uint8_t)(reg_addr >> 8));
    touch_wire->write((uint8_t)reg_addr);
    if ( touch_wire->endTransmission(true)){
       ep_string_control::ep_new_line_printf("The I2C transmission fails. - I2C Read");
        return -1;
    }
    touch_wire->requestFrom(driver_addr, length);
    for (int i = 0; i < length; i++) {
        *reg_data++ = touch_wire->read();
    }
    return 0;
}

bool touch_device::iic_write(uint8_t driver_addr, uint16_t reg_addr, const uint8_t *reg_data, uint32_t length) {
    touch_wire->beginTransmission(driver_addr);
    touch_wire->write((uint8_t)(reg_addr >> 8));
    touch_wire->write((uint8_t)reg_addr);
    for (int i = 0; i < length; i++) {
        touch_wire->write(*reg_data++);
    }
    if ( touch_wire->endTransmission(true))
    {
        ep_string_control::ep_new_line_printf("The I2C transmission fails. - I2C Write");
        return -1;
    }
    return 0;
}

uint16_t touch_device::read_config() {
    uint8_t buf[24];
    iic_write(CST328_ADDR, HYN_REG_MUT_DEBUG_INFO_MODE, buf, 0);
    iic_read(CST328_ADDR, HYN_REG_MUT_DEBUG_INFO_BOOT_TIME,buf, 4);
    iic_read(CST328_ADDR, HYN_REG_MUT_DEBUG_INFO_BOOT_TIME, buf, 4);
    iic_read(CST328_ADDR, HYN_REG_MUT_DEBUG_INFO_TP_NTX, buf, 24);
    iic_write(CST328_ADDR, HYN_REG_MUT_NORMAL_MODE, buf, 0);
    return (((uint16_t)buf[11] << 8) | buf[10]);
}

uint8_t touch_device::read_data() {
    uint8_t buf[41];
    uint8_t touch_cnt = 0;
    uint8_t clear = 0;
    uint8_t Over = 0xAB;
    size_t i = 0,num=0;
    iic_read(CST328_ADDR, ESP_LCD_TOUCH_CST328_READ_Number_REG, buf, 1);
    if ((buf[0] & 0x0F) == 0x00) {
        iic_write(CST328_ADDR, ESP_LCD_TOUCH_CST328_READ_Number_REG, &clear, 1);  // No touch data
        return 1;
    } else {
        /* Count of touched points */
        touch_cnt = buf[0] & 0x0F;
        if (touch_cnt > CST328_LCD_TOUCH_MAX_POINTS || touch_cnt == 0) {
            iic_write(CST328_ADDR, ESP_LCD_TOUCH_CST328_READ_Number_REG, &clear, 1);
            return true;
        }
        /* Read all points */
        iic_read(CST328_ADDR, ESP_LCD_TOUCH_CST328_READ_XY_REG, &buf[1], 27);
        /* Clear all */
        iic_write(CST328_ADDR, ESP_LCD_TOUCH_CST328_READ_Number_REG, &clear, 1);
        // printf(" points=%d \r\n",touch_cnt);
        if (ep_interrupt_control::ep_interrupt_disable()) {

            /* Number of touched points */
            if (touch_cnt > CST328_LCD_TOUCH_MAX_POINTS)
                touch_cnt = CST328_LCD_TOUCH_MAX_POINTS;
            points_ = (uint8_t) touch_cnt;
            /* Fill all coordinates */
            for (i = 0; i < touch_cnt; i++) {
                if (i > 0) num = 2;
                coords[i].x = (uint16_t) (((uint16_t) buf[(i * 5) + 2 + num] << 4) +
                                          ((buf[(i * 5) + 4 + num] & 0xF0) >> 4));
                coords[i].y = (uint16_t) (((uint16_t) buf[(i * 5) + 3 + num] << 4) + (buf[(i * 5) + 4 + num] & 0x0F));
                coords[i].strength = ((uint16_t) buf[(i * 5) + 5 + num]);
            }
            ep_interrupt_control::ep_interrupt_enable();
        }
    }
    return 0;
}

touch_device::touch_device(){
    touch_wire = &Wire;
    touch_wire->begin(CST328_SDA_PIN, CST328_SCL_PIN, I2C_MASTER_FREQ_HZ);
    pinMode(CST328_INT_PIN,INPUT);
    pinMode(CST328_RST_PIN,OUTPUT);

    touch_reset();
    auto verification= read_config();
    if(!((verification==0xcaca)? true: false)){
        ep_string_control::ep_new_line_printf("touch init failed");
    }
    ep_string_control::ep_new_line_printf("verification id : {}",verification);

    attachInterrupt(CST328_INT_PIN,interrupts_changes,RISING);
}

uint8_t touch_device::touch_reset() {
    digitalWrite(CST328_RST_PIN, HIGH );     // Reset
   ep_delay_control::ep_delay_os(50);
    digitalWrite(CST328_RST_PIN, LOW);
    ep_delay_control::ep_delay_os(5);
    digitalWrite(CST328_RST_PIN, HIGH );
    ep_delay_control::ep_delay_os(50);
    return true;
}

uint8_t touch_device::touch_read_x_y(uint16_t *x, uint16_t *y, uint16_t *strength, uint8_t *point_num, uint8_t max_point_num) {
    assert(x!= nullptr);
    assert(y!= nullptr);
    assert(point_num!= nullptr);
    assert(max_point_num>0);

    if (ep_interrupt_control::ep_interrupt_disable()) {
        if (this->points_ > max_point_num) {
            points_ = max_point_num;
        }
        for (int i = 0; i < points_; ++i) {
            x[i] = coords[i].x;
            y[i] = coords[i].y;
            if (strength) {
                strength[i] = coords[i].strength;
            }
        }
        *point_num = points_;
        points_ = 0;
        ep_interrupt_control::ep_interrupt_enable();
    }
    return (*point_num>0);
}

touch_device::~touch_device() {
    delete touch_wire;
    touch_wire= nullptr;
}

void touch_device::interrupts_changes() {
    touch_interrupts_= true;
}

bool touch_device::isTouchInterrupts() {
    return touch_interrupts_;
}

void touch_device::setTouchInterrupts(bool touchInterrupts) {
    touch_interrupts_ = touchInterrupts;
}
