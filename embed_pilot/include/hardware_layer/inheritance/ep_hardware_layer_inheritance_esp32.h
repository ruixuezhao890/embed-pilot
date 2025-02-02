/**
*********************************************************************
*********
* @project_name :micro_snow
* @file : ep_hardware_layer_inheritance_esp32.h
* @author : ruixuezhao890
* @brief : None
* @attention : None
* @date : 2024/12/24 
*********************************************************************
*********
*/


#ifndef MICRO_SNOW_EP_HARDWARE_LAYER_INHERITANCE_ESP32_H
#define MICRO_SNOW_EP_HARDWARE_LAYER_INHERITANCE_ESP32_H
#include "hardware_layer/abstract/ep_hardware_layer_abstract.h"

#ifdef HW_ESP32

#ifdef MICRO_SNOW
#include "device/device.h"
#endif

namespace ep_hw_inheritance{
    class hardware_inheritance_esp32:public ep_hw_abstract::hardware_abstract{
        display_device display_micro_snow_;
        touch_device touch_micro_snow_;
        gyroscope gyroscope_micro_snow_;
        wireless_device wireless_device_;
        rtc rtc_micro_snow_;
        button_phy button_phy_micro_snow_;
        fs_device fs_micro_snow_;
    public:
        hardware_inheritance_esp32();

        std::string type() override;

        void init() override;

    protected:
        ~hardware_inheritance_esp32() override;

    public:

        void Update_data() override;

        void File_system_init() override;

        void Display(lv_disp_drv_t *disp_drv, const lv_area_t *area, lv_color_t *color_p) override;

        void Touch(lv_indev_drv_t *indev_drv, lv_indev_data_t *data) override;

        void Get_imu_data_acceleration(ep_hw_abstract::imu_data &data) override;

        void Get_imu_data_gyroscope(ep_hw_abstract::imu_data &data) override;

        void Get_rtc_data_time(ep_hw_abstract::rtc_data_time &data) override;

        void Calibration_time() override;

        void Add_one_button(OneButton& config) override;

        void Deep_sleep() override;

        void Power_off() override;

        void Restart() override;

        void Is_connect_wifi(int & flag) override;

        uint16_t Get_battery_electric_quantity() override;
    };
}
#endif
#endif //MICRO_SNOW_EP_HARDWARE_LAYER_INHERITANCE_ESP32_H
