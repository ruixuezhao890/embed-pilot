/**
*********************************************************************
*********
* @project_name :embed_pilot
* @file : ep_config.h
* @author : ruixuezhao890
* @brief : None
* @attention : None
* @date : 2024/12/24 
*********************************************************************
*********
*/


#ifndef EMBED_PILOT_EP_CONFIG_H
#define EMBED_PILOT_EP_CONFIG_H


#define VERSION 0.1

#define MICRO_SNOW


#define HW_ESP32

#define DISP_BUFFER_NUM  2
#define EP_SCREEN_WIDTH  240
#define EP_SCREEN_HEIGHT 320


//#define EP_USE_STATIC_RAM

#define EP_USE_LVGL
//If you define this macro, it will increase the flash footprint by about 2.5kb
#define EP_USE_DEBUG

#define EP_USE_FMT_LIB


#define EP_USE_FREERTOS_THREAD_SAFE

#endif //EMBED_PILOT_EP_CONFIG_H
