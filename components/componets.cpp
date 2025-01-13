/**
*********************************************************************
*********
* @project_name :micro_snow
* @file : componets.cpp
* @author : ruixuezhao890
* @brief : None
* @attention : None
* @date : 2024/12/30 
*********************************************************************
*********
*/
#include "components/components.h"
#include "ep_lib.h"
namespace components{
    void components_init(){
        ep_string_control::ep_new_line_printf("\ncomponents init");
        /*lvgl初始化*/
        lv_init();
        lv_port_disp_init();
        lv_port_touch_init();
        lv_filesystem_fatfs_init();

        /*easylogger初始化*/
        elog_init();

        elog_set_fmt(ELOG_LVL_ASSERT, ELOG_FMT_ALL);
        elog_set_fmt(ELOG_LVL_ERROR, ELOG_FMT_LVL | ELOG_FMT_TIME | ELOG_FMT_T_INFO);
        elog_set_fmt(ELOG_LVL_WARN, ELOG_FMT_LVL | ELOG_FMT_T_INFO);
        elog_set_fmt(ELOG_LVL_INFO, ELOG_FMT_LVL);
        elog_set_fmt(ELOG_LVL_DEBUG, ELOG_FMT_ALL & ~ELOG_FMT_FUNC);

        /*Eenbale color*/
        elog_set_text_color_enabled(true);

        /* start EasyLogger */
        elog_start();

        ep_string_control::ep_new_line_printf("components init ok\n");
    }

}