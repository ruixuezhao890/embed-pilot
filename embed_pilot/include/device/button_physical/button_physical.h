/**
*********************************************************************
*********
* @project_name :micro_snow
* @file : button_physical_micro_snow.hpp
* @author : ruixuezhao890
* @brief : None
* @attention : None
* @date : 2025/1/2 
*********************************************************************
*********
*/


#ifndef MICRO_SNOW_BUTTON_PHYSICAL_HPP
#define MICRO_SNOW_BUTTON_PHYSICAL_HPP
#include "ep_config.h"
#ifdef MICRO_SNOW
#define PWR_KEY_PIN     6
#define LCD_BL_PIN      5
#define BAT_CONTROL_PIN 7
#define BAT_ADC_PIN     8

#include "vector"
#include "components/libraries/one_button/OneButton.h"
class button_phy{
    std::vector<OneButton> button_vec_;
public:
    button_phy();

    ~button_phy();

    void re_init();

    void add_one_button(OneButton& button);

    void monitor_button();

    void deep_sleep();

    void power_off();

    void  restart();

    uint16_t get_battery_electric_quantity();
};

#endif
#endif //MICRO_SNOW_BUTTON_PHYSICAL_MICRO_SNOW_HPP
