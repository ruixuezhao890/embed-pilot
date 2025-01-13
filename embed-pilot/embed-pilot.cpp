/**
*********************************************************************
*********
* @project_name :micro_snow
* @file : embed-pilot.cpp
* @author : ruixuezhao890
* @brief : None
* @attention : None
* @date : 2024/12/24 
*********************************************************************
*********
*/
#include "ep_lib.h"


using namespace embed_pilot;
ep_activate * ep_activate::instance_= nullptr;
app_package_base * ep_activate::app_desk_package_= nullptr;

const std::string embed_pilot_logo=R"(
                 _              _             _ _       _
   ___ _ __ ___ | |__   ___  __| |      _ __ (_| | ___ | |_
  / _ | '_ ` _ \| '_ \ / _ \/ _` |_____| '_ \| | |/ _ \| __|
 |  __| | | | | | |_) |  __| (_| |_____| |_) | | | (_) | |_
  \___|_| |_| |_|_.__/ \___|\__,_|     | .__/|_|_|\___/ \__|
                                       |_|
)";

#ifdef EP_USE_FREERTOS_THREAD_SAFE
SemaphoreHandle_t mutex_;
SemaphoreHandle_t m_mux;
#endif

void ep_activate::init() {
    //初始化设备
    app_manager_.destroy_all_apps();
    ep_string_control::ep_printf("{}",embed_pilot_logo);
    ep_string_control::ep_new_line_printf("\n- @author ruixuezao890");
    ep_string_control::ep_new_line_printf("- @version {:.1f}",VERSION);
    ep_string_control::ep_new_line_printf("- @build at {} {}\n",__TIME__,__DATE__);
}

void ep_activate::update() {
    //数据更新
    ep_hw_abstract::hardware_abstract::update_data();
    app_manager_.update();
}
