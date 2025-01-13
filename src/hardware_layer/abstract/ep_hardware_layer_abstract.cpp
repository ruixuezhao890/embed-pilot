/**
*********************************************************************
*********
* @project_name :micro_snow
* @file : hardware_layer_abstract.cpp
* @author : ruixuezhao890
* @brief : None
* @attention : None
* @date : 2024/12/24 
*********************************************************************
*********
*/



#include "hardware_layer/abstract/ep_hardware_layer_abstract.h"
namespace ep_hw_abstract{
    hardware_abstract * hardware_abstract:: hw_abstract_instance_= nullptr;

    hardware_abstract * hardware_abstract:: get_hw_instance(){
#ifdef FREERTOS_THREAD_SAFE
        if (hw_abstract_instance_== nullptr){
            if (xSemaphoreTake(mutex_,(TickType_t)10)==pdTRUE){
                if (hw_abstract_instance_== nullptr){
                    hw_abstract_instance_=new hardware_abstract();
                }
                xSemaphoreGive(mutex_);
            }
        }

#else
        if (hw_abstract_instance_== nullptr){
                hw_abstract_instance_=new hardware_abstract();
            }
#endif
        return hw_abstract_instance_;
    }

    void hardware_abstract:: release_hw_instance(){
        if (hw_abstract_instance_){
            delete hw_abstract_instance_;
            hw_abstract_instance_= nullptr;
            return;
        }
        ep_string_control::ep_new_line_printf("not exist");

    }
    void hardware_abstract:: inject_instance(ep_hw_abstract::hardware_abstract* inject){
        if (!inject){
            ep_string_control::ep_new_line_printf("invalid inject ptr");
        }

        if (!hw_abstract_instance_){
            hw_abstract_instance_=inject;
        }else{
            ep_string_control::ep_new_line_printf("abstract already exist");
        }
        inject->init();
        ep_string_control::ep_new_line_printf("\ninject type: {}",inject->type());
    }

    void hardware_abstract::update_data() {
        hw_abstract_instance_->Update_data();
    }

    void hardware_abstract::Update_data() {

    }

    void hardware_abstract::file_system_init() {
        hw_abstract_instance_->File_system_init();
    }

    void hardware_abstract::File_system_init() {

    }

    void hardware_abstract::display(lv_disp_drv_t *disp_drv, const lv_area_t *area, lv_color_t *color_p) {
        hw_abstract_instance_->Display(disp_drv,area,color_p);
    }

    void hardware_abstract::Display(lv_disp_drv_t *disp_drv, const lv_area_t *area, lv_color_t *color_p) {

    }

    void hardware_abstract::touch(lv_indev_drv_t *indev_drv, lv_indev_data_t *data) {
        hw_abstract_instance_->Touch(indev_drv,data);
    }

    void hardware_abstract::Touch(lv_indev_drv_t *indev_drv, lv_indev_data_t *data) {

    }

    void hardware_abstract::get_imu_data_acceleration(imu_data& data) {
        hw_abstract_instance_->Get_imu_data_acceleration(data);
    }

    void hardware_abstract::Get_imu_data_acceleration(imu_data& data) {

    }

    void hardware_abstract::get_imu_data_gyroscope(imu_data& data) {
       hw_abstract_instance_->Get_imu_data_gyroscope(data);
    }

    void hardware_abstract::Get_imu_data_gyroscope(imu_data& data) {

    }

    void hardware_abstract::get_rtc_data_time(rtc_data_time &data) {
        hw_abstract_instance_->Get_rtc_data_time(data);
    }

    void hardware_abstract::Get_rtc_data_time(rtc_data_time &data) {

    }

    uint16_t hardware_abstract::get_battery_electric_quantity() {
        return hw_abstract_instance_->Get_battery_electric_quantity();
    }

    uint16_t hardware_abstract::Get_battery_electric_quantity() {
        return 0;
    }

    void hardware_abstract::add_one_button(OneButton &config) {
        hw_abstract_instance_->Add_one_button(config);
    }

    void hardware_abstract::Add_one_button(OneButton &config) {

    }


    void hardware_abstract::deep_sleep() {
        hw_abstract_instance_->Deep_sleep();
    }

    void hardware_abstract::Deep_sleep() {

    }

    void hardware_abstract::power_off() {
        hw_abstract_instance_->Power_off();
    }

    void hardware_abstract::Power_off() {

    }

    void hardware_abstract::restart() {
        hw_abstract_instance_->Restart();
    }

    void hardware_abstract::Restart() {

    }


    void hardware_abstract::calibration_time() {
        hw_abstract_instance_->Calibration_time();
    }

    void hardware_abstract::Calibration_time() {

    }




    void hardware_abstract::connect_wifi(const char *ssid, const char *password) {

    }

    void hardware_abstract::Connect_wifi(const char *ssid, const char *password) {

    }

    void hardware_abstract::is_connect_wifi(int & flag) {
      hw_abstract_instance_->Is_connect_wifi(flag);
    }

    void hardware_abstract::Is_connect_wifi(int & flag) {

    }


}

