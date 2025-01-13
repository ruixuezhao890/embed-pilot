/**
*********************************************************************
*********
* @project_name :micro_snow
* @file : app_template.h
* @author : ruixuezhao890
* @brief : None
* @attention : None
* @date : 2024/12/30 
*********************************************************************
*********
*/


#ifndef MICRO_SNOW_APP_TEMPLATE_H
#define MICRO_SNOW_APP_TEMPLATE_H
#include "application/app_blueprint/app.h"

struct app_template_widget{

};

class app_template_ui:public ep_application::app_ui_base{
protected:
    void screen_init_function() override;
    app_template_widget widget;
public:
    void * get_screen_widget() override{
        return (void *)&widget;
    }
};
class app_template : public ep_application::app_base{
    app_template_widget * widget_{};

    app_template_ui * app_template_ui_{};
public:
    app_template_widget * get_app_template_ui_widget();

    app_template_ui * get_app_desk_ui();

    app_template();

    ~app_template() override;

    void *ui_create() override;

    void set_whether_the_previous_screen_is_cleared() override;

    void on_create() override;

    void on_resume() override;

    void on_running() override;

    void on_running_background_running() override;

    void on_pause() override;

    void on_destroy() override;
};

class app_template_packager:public ep_application::app_package_base{
public:
    ~app_template_packager() override = default;

    std::string get_app_name() override {
        return "template";
    }

    void *get_icon() override {
        return app_package_base::get_icon();
    }

    void *get_custom_data() override {
        return app_package_base::get_custom_data();
    }

    void *new_app() override {
        return new app_template();
    }

    void delete_app(void *app) override {
        if (app){
            delete (app_template *)app;
        }

    }
};

#endif //MICRO_SNOW_APP_TEMPLATE_H
