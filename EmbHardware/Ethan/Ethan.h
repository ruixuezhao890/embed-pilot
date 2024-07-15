/**
*********************************************************************
*********
* @project_name :chip_arch_demo
* @file : Ethan.h
* @author : zen3
* @brief : None
* @attention : None
* @date : 2024/6/23 
*********************************************************************
*********
*/
//

#ifndef CHIP_ARCH_DEMO_ETHAN_H
#define CHIP_ARCH_DEMO_ETHAN_H
#include "ChipArch/EmbHardware/HAL.h"
#if STM32&&MCU
class Ethan:public HAL{
public:
    String type() override;

    void init() override;

    void delay(unsigned long milliseconds) override;

    void display(lv_disp_drv_t *disp_drv, const lv_area_t *area, lv_color_t *color_p) override;

    void keyboard_read(lv_indev_data_t *data) override;

    void touchpad_point_read(lv_indev_data_t *data) override;

    void up_date() override;
};

#endif
#endif //CHIP_ARCH_DEMO_ETHAN_H
