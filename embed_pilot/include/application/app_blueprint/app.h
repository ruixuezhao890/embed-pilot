/**
*********************************************************************
*********
* @project_name :micro_snow
* @file : app.h
* @author : ruixuezhao890
* @brief : None
* @attention : None
* @date : 2024/12/24 
*********************************************************************
*********
*/


#ifndef MICRO_SNOW_APP_H
#define MICRO_SNOW_APP_H
#include <string>
#include <sstream>
#include "lvgl.h"
#include "../components/eez_stduio/compatible.hpp"
namespace ep_application{

    class app_package_base{
    private:
        void * user_data_;

        uint8_t app_package_id_;
    public:
        app_package_base():user_data_(nullptr),app_package_id_(0){}

        inline void set_app_package_id(uint8_t id){app_package_id_=id;}

        inline uint8_t get_app_package_id(){return app_package_id_;}

        virtual ~app_package_base()= default;

        inline void set_user_data(void * user_data){ user_data_=user_data;}

        inline void * get_user_data(){return user_data_;}

        inline app_package_base * get_app_package_address(){return this;}

        virtual std::string get_app_name()=0;

        virtual void * get_icon(){return nullptr;}

        virtual void * get_custom_data(){return nullptr;}

        virtual void * new_app(){return nullptr;}

        virtual void delete_app(void * app){ }
    };

    class app_ui_base{
    protected:
        lv_obj_t * screen_obj_t{};

        void * user_date_= nullptr;

    protected:
        virtual void screen_init_function()=0;
    public:
        void set_user_date(void * set){
            user_date_=set;
        }

        void * get_user_date(){
            return user_date_;
        }

        virtual void * get_screen_widget(){return nullptr;}

        virtual int16_t get_screen_id(){return -1;}

        void on_hide(){
            lv_obj_add_flag(screen_obj_t,LV_OBJ_FLAG_HIDDEN);
        }
        void on_show(){
            lv_obj_clear_flag(screen_obj_t,LV_OBJ_FLAG_HIDDEN);
        }
        void on_create(){

            screen_init_function();
            screen_obj_t=lv_scr_act();
        }
        //更新控件数据专用函数
         void on_foreground(){

        }
    };

    class app_base{
    private:


      bool allow_background_running_;
      bool go_start_;
      bool go_close_;
      bool go_destroy_;

    protected:
        app_package_base * app_packager_;

        app_ui_base * app_ui_;

    public:
        inline void set_allow_background_running(bool allow){allow_background_running_=allow;}

        inline void start_app(){go_start_= true;}

        inline void close_app(){go_close_= true;}

        inline void destroy_app(){go_destroy_= true;}


        app_base()
        :app_packager_(nullptr),
         app_ui_(nullptr),
         allow_background_running_(false),
         go_start_(false),
         go_destroy_(false),
         go_close_(false){}

         virtual ~app_base(){
             printf("~app_base\n");
          // ! app_packager_ 更本不需要释放，再一次的创建app没有new新的packager只是去对应的vector获取，所以不能释放
             if(app_ui_ != nullptr){
                 delete app_ui_;
                 app_ui_ = nullptr;
             }
        };

        inline void delete_app_pointer(void * app){app_packager_->delete_app(app);}
        inline std::string get_app_name(){return app_packager_->get_app_name();}
        inline void * get_app_icon(){return app_packager_->get_icon();}
        inline void * get_app_custom_data(){return app_packager_->get_custom_data();}
        inline void * get_user_data(){return app_packager_->get_user_data();}


        inline bool is_allow_background_running(){return allow_background_running_;}
        inline bool is_going_start(){return go_start_;}
        inline bool is_going_close(){return go_close_;}
        inline bool is_going_destroy(){return go_destroy_;}

        inline void reset_going_start_flag(){go_start_=false;}
        inline void reset_going_close_flag(){go_close_=false;}
        inline void reset_going_destroy_flag(){go_destroy_=false;}


        inline void set_app_packager(app_package_base* app_packager){
            app_packager_=app_packager;
        }
        inline void set_app_ui(app_ui_base * app_ui){
            app_ui_=app_ui;
        }

        //创建ui界面再通过set_app_ui进行设置
        virtual void * ui_create(){
            return nullptr;
        }

        void ui_on_create(){
            app_ui_->on_create();
        }

        void ui_on_foreground(){
            app_ui_->on_foreground();
        }

        void ui_on_hide(){
            app_ui_->on_hide();
        }

        void ui_on_show(){
            app_ui_->on_show();
        }

        virtual void on_create(){}
        virtual void on_resume(){}
        virtual void on_running(){}
        virtual void on_running_background_running(){}
        virtual void on_pause(){}
        virtual void on_destroy(){}
    };
}
#endif //MICRO_SNOW_APP_H
