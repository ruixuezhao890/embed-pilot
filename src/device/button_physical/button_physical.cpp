/**
*********************************************************************
*********
* @project_name :micro_snow
* @file : button_physical_micro_snow.cpp
* @author : ruixuezhao890
* @brief : None
* @attention : None
* @date : 2025/1/2 
*********************************************************************
*********
*/
#include "device/button_physical/button_physical.h"
#include "ep_lib.h"
button_phy::button_phy() {
  re_init();
}

button_phy::~button_phy() {
    button_vec_.clear();
}

void button_phy::re_init() {
    button_vec_.clear();
    pinMode(PWR_KEY_PIN, INPUT);
    pinMode(BAT_CONTROL_PIN,OUTPUT);
    digitalWrite(BAT_CONTROL_PIN,LOW);
    ep_delay_control::ep_delay_os(100);
    if (!digitalRead(PWR_KEY_PIN)){
        digitalWrite(BAT_CONTROL_PIN,HIGH);
    }
    //todo 电源管理单独抽出来用一个应用来实现，为了实现长按选择关机还是重启
}

void button_phy::add_one_button(OneButton &button) {
    button_vec_.push_back(button);
}

void button_phy::monitor_button() {
    for(auto &item:button_vec_){
        item.tick();
    }
}

//todo 未来添加
void button_phy::deep_sleep() {
    ep_string_control::ep_new_line_printf("deep_sleep");
}

void button_phy::power_off() {
    ep_string_control::ep_new_line_printf("power_off");
}

void button_phy::restart() {
    ep_string_control::ep_new_line_printf("restart");
}

uint16_t button_phy::get_battery_electric_quantity() {
    ep_string_control::ep_new_line_printf("bat quantity");
    return 0;
}


