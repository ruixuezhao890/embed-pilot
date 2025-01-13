/**
*********************************************************************
*********
* @project_name :micro_snow
* @file : display.cpp
* @author : ruixuezhao890
* @brief : None
* @attention : None
* @date : 2024/12/30
*********************************************************************
*********
*/

#include "device/display/display.h"

display_device::display_device() {
    tft_micro_snow_= new TFT_eSPI(EP_SCREEN_WIDTH,EP_SCREEN_HEIGHT);
    display_init(0,TFT_WHITE);
}

void display_device::display_init(uint8_t set_rotation, uint32_t color_init) {
    tft_micro_snow_->begin();
    tft_micro_snow_->setRotation(set_rotation);
    tft_micro_snow_->fillScreen(color_init);
}

void display_device::draw_color_on_the_screen(uint16_t x_start, uint16_t y_start, uint16_t x_end, uint16_t y_end,
                                                  uint16_t *color_p) {
    uint32_t width=(x_end-x_start +1);
    uint32_t height=(y_end-y_start +1);

    tft_micro_snow_->startWrite();
    tft_micro_snow_->setAddrWindow(x_start,y_start,width,height);
    tft_micro_snow_->pushColors(color_p,width*height, true);
    tft_micro_snow_->endWrite();
}

display_device::~display_device() {
    delete tft_micro_snow_;
    tft_micro_snow_= nullptr;
}
