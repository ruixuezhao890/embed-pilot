/**
*********************************************************************
*********
* @project_name :micro_snow
* @file : app_desk.h
* @author : ruixuezhao890
* @brief : None
* @attention : None
* @date : 2024/12/30 
*********************************************************************
*********
*/


#ifndef MICRO_SNOW_APP_TEMPLATE_H
#define MICRO_SNOW_APP_TEMPLATE_H
#include "../include/application/app_blueprint/app.h"

struct app_desk_widget{
    uint8_t app_index;
    uint8_t app_click_enable;
    uint8_t weather_change_flag;
    lv_obj_t * app_icon_img;
    lv_obj_t * time_label0;
    lv_obj_t * time_label1;
    lv_obj_t * app_install_panel;
};

namespace public_search_weather_api{
    std::string get_url(const std::string& city);
    void search_weather_start();
    void set_search_city(const std::string & city);
    std::string &get_search_city();
    const std::string get_weather_city();
    int& get_update_flag();
}
class app_desk_ui:public ep_application::app_ui_base{
protected:
    void screen_init_function() override;
    app_desk_widget widget;

    void desk_ui_init();

    void on_foreground() override;

public:
    app_desk_widget & get_screen_widget_child(){
        return widget;
    }

    void * get_screen_widget() override{
        return (void *)&widget;
    }

    void monitor_weather_change(const std::string Weather);

};
class app_desk : public ep_application::app_base{
    app_desk_widget * widget_{};

    app_desk_ui * app_desk_ui_{};


protected:
    void app_icon_draw();

    void monitor_app_open();

    void monitor_weather_changes();

public:
    app_desk_widget * get_app_desk_ui_widget();

    app_desk_ui * get_app_desk_ui();

    app_desk();

    ~app_desk() override;

    void *ui_create() override;

    void set_whether_the_previous_screen_is_cleared() override;

    void on_create() override;

    void on_resume() override;

    void on_running() override;

    void on_running_background_running() override;

    void on_pause() override;

    void on_destroy() override;
};

class app_desk_packager:public ep_application::app_package_base{
public:
    ~app_desk_packager() override = default;

    std::string get_app_name() override {
        return "desk";
    }

    void *get_icon() override {
        return app_package_base::get_icon();
    }

    void *get_custom_data() override {
        return app_package_base::get_custom_data();
    }

    void *new_app() override {
        return new app_desk();
    }

    void delete_app(void *app) override {
        delete (app_desk *)app;
    }
};


extern "C"{
LV_IMG_DECLARE(ui__temporary_image);
LV_IMG_DECLARE(ui_img_2051629593);    // assets/雨.png
LV_IMG_DECLARE(ui_img_defaut_png);
}
#endif //MICRO_SNOW_APP_TEMPLATE_H
