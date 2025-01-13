/**
*********************************************************************
*********
* @project_name :micro_snow
* @file : ep_service.cpp
* @author : ruixuezhao890
* @brief : None
* @attention : None
* @date : 2024/12/24 
*********************************************************************
*********
*/


#include "ep_api.h"
#include "components/libraries/fmt_lib/fmt/core.h"
#include "application/app_blueprint/app_install.h"
#include "hardware_layer/inheritance/ep_hardware_layer_inheritance_esp32.h"
#include "components/components.h"

static embed_pilot::ep_activate *  ep_control= nullptr;
using namespace ep_hw_abstract;
namespace ep_auto_init_control{
    void ep_auto_init(){
#ifdef EP_USE_FREERTOS_THREAD_SAFE
        mutex_=xSemaphoreCreateMutex();
        m_mux=xSemaphoreCreateMutex();
#endif
       ep_control=embed_pilot::ep_activate::get_instance();
       //框架初始化
       ep_control->init();

       //注入硬件依赖+初始化
        hardware_abstract::inject_instance(new ep_hw_inheritance::hardware_inheritance_esp32());


       //组件初始化
        components::components_init();


        //安装程序
       ep_install_app_function(ep_control);
       //得到desk应用的package
       auto desk_package=ep_control->get_installed_app_from_index(0);
       //设置package
        embed_pilot::ep_activate::set_app_desk_package(desk_package);
       //启动第一个程序
        ep_control->create_start_app(desk_package);
    }
};

namespace ep_data_up_control{
    void ep_data_up(){
      ep_control->update();
    }
};

namespace ep_interrupt_control{
    void ep_interrupt_enable(){
#ifdef EP_USE_FREERTOS_THREAD_SAFE
        xSemaphoreGive(m_mux);
#else
#endif
    }
    bool ep_interrupt_disable(){
#ifdef EP_USE_FREERTOS_THREAD_SAFE
        return (xSemaphoreTake(m_mux, 50) == pdTRUE);
#else
#endif
    }
};

namespace ep_delay_control{
    void ep_delay_us(uint32_t nums){
        delayMicroseconds(nums);
    }
    void ep_delay_ms(uint32_t nums){
        delay(nums);
    }

#ifdef EP_USE_FREERTOS_THREAD_SAFE
    void ep_delay_os(uint32_t nums){
        vTaskDelay(nums);
    }
#endif
};


