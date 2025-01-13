/**
*********************************************************************
*********
* @project_name :micro_snow
* @file : display_micro_snow.hpp
* @author : ruixuezhao890
* @brief : None
* @attention : None
* @date : 2024/12/30 
*********************************************************************
*********
*/


#ifndef MICRO_SNOW_DISPLAY_HPP
#define MICRO_SNOW_DISPLAY_HPP

#include "ep_config.h"
#ifdef MICRO_SNOW
#include "TFT_eSPI.h"


class display_device{

    TFT_eSPI * tft_micro_snow_;
public:
    display_device();

    ~display_device();

    void display_init(uint8_t set_rotation,uint32_t color_init);

    void draw_color_on_the_screen(uint16_t x_start, uint16_t y_start, uint16_t x_end, uint16_t y_end,uint16_t* color_p);
};
#endif


#endif //MICRO_SNOW_DISPLAY_MICRO_SNOW_HPP
