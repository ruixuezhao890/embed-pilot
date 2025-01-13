/**
*********************************************************************
*********
* @project_name :micro_snow
* @file : ep_def.h
* @author : ruixuezhao890
* @brief : None
* @attention : None
* @date : 2024/12/24 
*********************************************************************
*********
*/


#ifndef MICRO_SNOW_EP_DEF_H
#define MICRO_SNOW_EP_DEF_H

#include "ep_config.h"

#ifdef ARDUINO
#include <Arduino.h>
#endif

#ifdef EP_USE_LVGL
#include <lvgl.h>
#endif

#include "application/app_blueprint/app.h"
#include "application/app_blueprint/app_register.h"
#include "application/app_manager/app_manger.h"

#define EP_EOK                          (0)                         /**< No error */
#define EP_ENOMEM                       (-1)                        /**< No enough memory */
#define EP_EIO                          (-2)                        /**< I/O error */
#define EP_ENOTFOUND                    (-3)                        /**< Not found */
#define EP_EBUSY                        (-4)                        /**< Resource busy */
#define EP_EEXIST                       (-5)                        /**< Exists */
#define EP_ENOTSUP                      (-6)                        /**< Operation not supported */
#define EP_EINVAL                       (-7)                        /**< Invalid argument */
#define EP_ETIMEOUT                     (-8)                        /**< Timeout */

#ifdef EP_USE_FREERTOS_THREAD_SAFE
#include "FreeRTOS.h"
#include "semphr.h"
extern SemaphoreHandle_t mutex_;
extern SemaphoreHandle_t m_mux;
#endif

namespace embed_pilot{
using namespace ep_application;
    //采用单例模式，让全局都可以进行访问
    class ep_activate{
        static ep_activate * instance_;

        static app_package_base * app_desk_package_;

        app_register app_register_;

        app_manager app_manager_;

        void * user_data_;

        ep_activate():user_data_(nullptr){};

        ~ep_activate()= default;
    public:
        ep_activate(const ep_activate&)=delete;
        ep_activate& operator=(const ep_activate&)=delete;

        static ep_activate * get_instance(){
#ifdef EP_USE_FREERTOS_THREAD_SAFE
            if (instance_== nullptr){
                if (xSemaphoreTake(mutex_,(TickType_t)10)==pdTRUE){
                    if (instance_== nullptr){
                        instance_=new ep_activate();
                    }
                    xSemaphoreGive(mutex_);
                }
            }

#else
            if (instance_== nullptr){
                instance_=new ep_activate();
            }
#endif
            return instance_;
        }

        static void release_instance(){
            if (instance_){
                delete instance_;
                instance_= nullptr;
            }
        }

        static app_package_base * get_app_desk_package(){
            return app_desk_package_;
        }

        static void set_app_desk_package(app_package_base* set){
            app_desk_package_=set;
        }

        inline void set_user_data(void* user_data){user_data_=user_data;}

        inline void * get_user_data(){return user_data_;}

        void init();

        void update();

        inline bool install_app(app_package_base * app_packer){
            return app_register_.install(app_packer,user_data_);
        }

        inline bool uninstall(app_package_base * app_packer){
            return app_register_.uninstall(app_packer);
        }

        inline void uninstall_all_apps(){app_register_.uninstall_all_apps();}

        inline std::size_t get_installed_app_num(){return app_register_.get_install_app_num();}

        inline app_package_base* get_installed_app_from_index(uint8_t id){ return app_register_.get_install_app_package(id);}

        inline app_package_base* get_installed_app_from_name(const char * app_name){ return app_register_.get_install_app_package(app_name);}

        inline app_base * create_app(app_package_base * app_package){
            return app_manager_.create_app(app_package);
        }

        inline bool start_app(app_base * app){return app_manager_.start_app(app);}

        inline bool create_start_app(app_package_base * app_package){
            return start_app(create_app(app_package));
        }

        inline bool close_app(app_base * app){
            return app_manager_.close_app(app);
        }

        inline bool destroy_app(app_base * app){return app_manager_.destroy_app(app);}

        inline void destroy_all_apps(){app_manager_.destroy_all_apps();}

        inline size_t get_created_app_num(){return app_manager_.get_created_app_num();}

        /*下面是输入设备相关的api先不写空着
         * todo */
    };


}
#endif //MICRO_SNOW_EP_DEF_H
