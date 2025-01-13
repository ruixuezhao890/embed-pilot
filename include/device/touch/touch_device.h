/**
*********************************************************************
*********
* @project_name :micro_snow
* @file : touch_micro_snow.hpp
* @author : ruixuezhao890
* @brief : None
* @attention : None
* @date : 2024/12/30 
*********************************************************************
*********
*/


#ifndef MICRO_SNOW_TOUCH_H
#define MICRO_SNOW_TOUCH_H
#include "ep_lib.h"

#ifdef MICRO_SNOW
#include <Wire.h>
#define CST328_ADDR 0x1A
#define CST328_SDA_PIN       1
#define CST328_SCL_PIN       3
#define CST328_INT_PIN       4
#define CST328_RST_PIN       2
#define I2C_MASTER_FREQ_HZ  400000                     /*!< I2C master clock frequency */


#define CST328_LCD_TOUCH_MAX_POINTS             (5)
/* CST328 registers */
#define ESP_LCD_TOUCH_CST328_READ_Number_REG    (0xD005)
#define ESP_LCD_TOUCH_CST328_READ_XY_REG        (0xD000)
#define ESP_LCD_TOUCH_CST328_READ_Checksum_REG  (0x80FF)
#define ESP_LCD_TOUCH_CST328_CONFIG_REG         (0x8047)

//debug info
/****************HYN_REG_MUT_DEBUG_INFO_MODE address start***********/
#define HYN_REG_MUT_DEBUG_INFO_IC_CHECKSUM      0xD208
#define HYN_REG_MUT_DEBUG_INFO_FW_VERSION       0xD204
#define HYN_REG_MUT_DEBUG_INFO_IC_TYPE			    0xD202
#define HYN_REG_MUT_DEBUG_INFO_PROJECT_ID			  0xD200
#define HYN_REG_MUT_DEBUG_INFO_BOOT_TIME        0xD1FC
#define HYN_REG_MUT_DEBUG_INFO_RES_Y            0xD1FA
#define HYN_REG_MUT_DEBUG_INFO_RES_X            0xD1F8
#define HYN_REG_MUT_DEBUG_INFO_KEY_NUM          0xD1F7
#define HYN_REG_MUT_DEBUG_INFO_TP_NRX           0xD1F6
#define HYN_REG_MUT_DEBUG_INFO_TP_NTX           0xD1F4
//workmode
#define HYN_REG_MUT_DEBUG_INFO_MODE             0xD101
#define HYN_REG_MUT_RESET_MODE            		  0xD102
#define HYN_REG_MUT_DEBUG_RECALIBRATION_MODE    0xD104
#define HYN_REG_MUT_DEEP_SLEEP_MODE    			    0xD105
#define HYN_REG_MUT_DEBUG_POINT_MODE	    	    0xD108
#define HYN_REG_MUT_NORMAL_MODE                 0xD109

#define HYN_REG_MUT_DEBUG_RAWDATA_MODE          0xD10A
#define HYN_REG_MUT_DEBUG_DIFF_MODE             0xD10D
#define HYN_REG_MUT_DEBUG_FACTORY_MODE          0xD119
#define HYN_REG_MUT_DEBUG_FACTORY_MODE_2        0xD120

//Interrupt Modes
#define RISING    0x01
#define FALLING   0x02
#define CHANGE    0x03
#define ONLOW     0x04
#define ONHIGH    0x05
#define ONLOW_WE  0x0C
#define ONHIGH_WE 0x0D

class touch_device{
    static bool touch_interrupts_;
    uint8_t points_;
public:
    static bool isTouchInterrupts();

    static void setTouchInterrupts(bool touchInterrupts);

private:
    struct {
        uint16_t x;
        uint16_t y;
        uint16_t strength;
    }coords[CST328_LCD_TOUCH_MAX_POINTS];

    TwoWire * touch_wire;
protected:
    bool iic_read(uint8_t driver_addr, uint16_t reg_addr, uint8_t * reg_data, uint32_t length);
    bool iic_write(uint8_t driver_addr, uint16_t reg_addr, const uint8_t *reg_data, uint32_t length);

    static void interrupts_changes();

    uint16_t  read_config();

public:
    touch_device();
    ~touch_device();
    uint8_t touch_reset();
    uint8_t  read_data();
    uint8_t touch_read_x_y(uint16_t * x, uint16_t *y, uint16_t *strength, uint8_t *point_num, uint8_t max_point_num);
};

#endif
#endif //MICRO_SNOW_TOUCH_MICRO_SNOW_H
