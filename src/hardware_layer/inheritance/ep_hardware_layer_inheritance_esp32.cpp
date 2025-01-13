/**
*********************************************************************
*********
* @project_name :micro_snow
* @file : ep_hardware_layer_inheritance_esp32.cpp
* @author : ruixuezhao890
* @brief : None
* @attention : None
* @date : 2024/12/24 
*********************************************************************
*********
*/




#include "hardware_layer/inheritance/ep_hardware_layer_inheritance_esp32.h"
#ifdef HW_ESP32
#define SSID "wifiwifi"
#define PASSWORD "2479620061"
namespace ep_hw_inheritance{

    hardware_inheritance_esp32::hardware_inheritance_esp32() {
        Serial.begin(115200);
        Wire1.begin( 11, 10);
    }

    hardware_inheritance_esp32::~hardware_inheritance_esp32(){

    }

    void hardware_inheritance_esp32::Update_data() {
        button_phy_micro_snow_.monitor_button();

    }

    void hardware_inheritance_esp32::File_system_init() {
        fs_micro_snow_.re_init();
    }

    void hardware_inheritance_esp32::Display(lv_disp_drv_t *disp_drv, const lv_area_t *area, lv_color_t *color_p) {
        display_micro_snow_.draw_color_on_the_screen(area->x1,area->y1,area->x2,area->y2,(uint16_t *)color_p);
        lv_disp_flush_ready(disp_drv);
    }

    void hardware_inheritance_esp32::Touch(lv_indev_drv_t *indev_drv, lv_indev_data_t *data) {
        uint16_t touchpad_x[5] = {0};
        uint16_t touchpad_y[5] = {0};
        uint16_t strength[5]   = {0};
        uint8_t touchpad_cnt = 0;
        touch_micro_snow_.read_data();
        uint8_t touchpad_pressed = touch_micro_snow_.touch_read_x_y(touchpad_x, touchpad_y, strength, &touchpad_cnt, CST328_LCD_TOUCH_MAX_POINTS);
        if (touchpad_pressed && touchpad_cnt > 0 ) {
            data->point.x = touchpad_x[0];
            data->point.y = touchpad_y[0];
            data->state = LV_INDEV_STATE_PR;
//        ep_string_control::ep_new_line_printf("LVGL  : X={} Y={} num={}\r\n", touchpad_x[0], touchpad_y[0],touchpad_cnt);
        } else {
            data->state = LV_INDEV_STATE_REL;
        }

    }

    std::string hardware_inheritance_esp32::type() {
        return "esp32_inheritance";
    }

    void hardware_inheritance_esp32::init() {
        wireless_device_.wifi_connect(SSID,PASSWORD);
        rtc_micro_snow_.re_init(&wireless_device_);
        rtc_micro_snow_.calibration_time();
    }

    void hardware_inheritance_esp32::Get_imu_data_acceleration(ep_hw_abstract::imu_data &data) {
        IMUdata udata;
        gyroscope_micro_snow_.get_imu_data_acceleration(udata);
        data.x=udata.x;
        data.y=udata.y;
        data.z=udata.z;
    }

    void hardware_inheritance_esp32::Get_imu_data_gyroscope(ep_hw_abstract::imu_data &data) {
        IMUdata udata;
        gyroscope_micro_snow_.get_imu_data_gyroscope(udata);
        data.x=udata.x;
        data.y=udata.y;
        data.z=udata.z;
    }

    void hardware_inheritance_esp32::Get_rtc_data_time(ep_hw_abstract::rtc_data_time &data) {
        ep_hw_abstract::rtc_data_time data_rtc_raw;
        rtc_micro_snow_.read_time(data_rtc_raw);
       data.year=data_rtc_raw.year;
       data.month=data_rtc_raw.month;
       data.day=data_rtc_raw.day;
       data.hour=data_rtc_raw.hour;
       data.minute=data_rtc_raw.minute;
       data.second=data_rtc_raw.second;
    }

    void hardware_inheritance_esp32::Calibration_time() {
        rtc_micro_snow_.calibration_time();
    }

    void hardware_inheritance_esp32::Add_one_button(OneButton &config) {
       button_phy_micro_snow_.add_one_button(config);
    }

    void hardware_inheritance_esp32::Deep_sleep() {
        button_phy_micro_snow_.deep_sleep();
    }

    void hardware_inheritance_esp32::Power_off() {
        button_phy_micro_snow_.power_off();
    }

    void hardware_inheritance_esp32::Restart(){
        button_phy_micro_snow_.restart();
    }

    void hardware_inheritance_esp32::Is_connect_wifi(int & flag) {
        flag=wireless_device_.isWifiConnection();
    }

    uint16_t hardware_inheritance_esp32::Get_battery_electric_quantity() {
       return button_phy_micro_snow_.get_battery_electric_quantity();
    }
}
#endif

