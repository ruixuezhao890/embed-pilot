/**
*********************************************************************
*********
* @project_name :micro_snow
* @file : lvgl_port_indev.cpp
* @author : ruixuezhao890
* @brief : None
* @attention : None
* @date : 2024/12/30 
*********************************************************************
*********
*/
#include "components/lvgl_porting/lvgl_port_indevice.h"
#include "ep_lib.h"

static lv_indev_t * input_device_touchpad;

void lv_port_touch_init(){
    static lv_indev_drv_t indev_drv;
    lv_indev_drv_init(&indev_drv);
    indev_drv.type=LV_INDEV_TYPE_POINTER;
    indev_drv.read_cb=ep_hw_abstract::hardware_abstract::touch;
    input_device_touchpad= lv_indev_drv_register(&indev_drv);
}