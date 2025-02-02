/**
*********************************************************************
*********
* @project_name :micro_snow
* @file : lvgl_port_disp.cpp
* @author : ruixuezhao890
* @brief : None
* @attention : None
* @date : 2024/12/30 
*********************************************************************
*********
*/
#include "components/lvgl_porting/lvgl_port_disp.h"
#include "ep_lib.h"
void lv_port_disp_init(){

#if DISP_BUFFER_NUM==1
    static lv_disp_draw_buf_t draw_buf_dsc;
#ifdef SRAM
    static lv_color_t buf_1 = mymalloc(SRAMEX, MY_DISP_HOR_RES * MY_DISP_VER_RES);              /* 设置缓冲区的大小为屏幕的全尺寸大小 */
    lv_disp_draw_buf_init(&draw_buf_dsc, buf_1, NULL, MY_DISP_HOR_RES * MY_DISP_VER_RES);     /* 初始化显示缓冲区 */
#else
    static lv_color_t buf_1[EP_SCREEN_WIDTH * 10];                                              /* 设置缓冲区的大小为 10 行屏幕的大小 */
    lv_disp_draw_buf_init(&draw_buf_dsc, buf_1, NULL, EP_SCREEN_WIDTH * 10);                  /* 初始化显示缓冲区 */
#endif
#elif DISP_BUFFER_NUM ==2
    #ifdef  SRAM
    static lv_disp_draw_buf_t draw_buf_dsc;
//   static lv_color_t buf_1[MY_DISP_HOR_RES * 10];                                            /* 设置缓冲区的大小为 10 行屏幕的大小 */
//   static lv_color_t buf_2[MY_DISP_HOR_RES * 10];/* 设置另一个缓冲区的大小为 10 行屏幕的大小 */
    auto buf_1=new lv_color_t[MY_DISP_HOR_RES* 10];
    auto buf_2=new lv_color_t[MY_DISP_HOR_RES* 10];
   lv_disp_draw_buf_init(&draw_buf_dsc, buf_1, buf_2, MY_DISP_HOR_RES * 10);
#else
   static lv_disp_draw_buf_t draw_buf_dsc;
   static lv_color_t buf_1[EP_SCREEN_WIDTH * 10];                                            /* 设置缓冲区的大小为 10 行屏幕的大小 */
   static lv_color_t buf_2[EP_SCREEN_HEIGHT * 10];                                            /* 设置另一个缓冲区的大小为 10 行屏幕的大小 */
   lv_disp_draw_buf_init(&draw_buf_dsc, buf_1, buf_2, EP_SCREEN_WIDTH * 10);             /* 初始化显示缓冲区 */
#endif
#elif DISP_BUFFER_NUM ==3
    #if SRAM

#else
    disp_drv.full_refresh = 1
    static lv_disp_draw_buf_t draw_buf_dsc;
    static lv_color_t buf_1[MY_DISP_HOR_RES * MY_DISP_VER_RES];                               /* 设置一个全尺寸的缓冲区 */
    static lv_color_t buf_2[MY_DISP_HOR_RES * MY_DISP_VER_RES];                               /* 设置另一个全尺寸的缓冲区 */
    lv_disp_draw_buf_init(&draw_buf_dsc, buf_1, buf_2, MY_DISP_HOR_RES * MY_DISP_VER_RES);/* 初始化显示缓冲区 */
#endif
#endif



    /*-----------------------------------
     * 在 LVGL 中注册显示设备
     *----------------------------------*/

    static lv_disp_drv_t disp_drv;                  /* 显示设备的描述符 */
    lv_disp_drv_init(&disp_drv);                    /* 初始化为默认值 */

    disp_drv.hor_res = EP_SCREEN_WIDTH;
    disp_drv.ver_res = EP_SCREEN_HEIGHT;

    /* 用来将缓冲区的内容复制到显示设备 */
    disp_drv.flush_cb = ep_hw_abstract::hardware_abstract::display;

    /* 设置显示缓冲区 */
    disp_drv.draw_buf = &draw_buf_dsc;

    /* 如果您有GPU，请使用颜色填充内存阵列
     * 注意，你可以在 lv_conf.h 中使能 LVGL 内置支持的 GPUs
     * 但如果你有不同的 GPU，那么可以使用这个回调函数。 */
    //disp_drv.gpu_fill_cb = gpu_fill;

    /* 注册显示设备 */
    lv_disp_drv_register(&disp_drv);
}