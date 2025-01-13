/**
*********************************************************************
*********
* @project_name :micro_snow
* @file : app_novel.h
* @author : ruixuezhao890
* @brief : None
* @attention : None
* @date : 2024/12/30 
*********************************************************************
*********
*/


#ifndef MICRO_SNOW_APP_NOVEL_H
#define MICRO_SNOW_APP_NOVEL_H
#include "application/app_blueprint/app.h"

struct app_novel_widget{

};

class app_novel_ui:public ep_application::app_ui_base{
protected:
    void screen_init_function() override;
    app_novel_widget widget;
public:
    void * get_screen_widget() override{
        return (void *)&widget;
    }
};
class app_novel : public ep_application::app_base{
    app_novel_widget * widget_{};
public:
    app_novel_widget * get_app_novel_ui_widget();

    app_novel();

    ~app_novel() override;

    void *ui_create() override;

    void on_create() override;

    void on_resume() override;

    void on_running() override;

    void on_running_background_running() override;

    void on_pause() override;

    void on_destroy() override;
};

class app_novel_packager:public ep_application::app_package_base{
public:
    ~app_novel_packager() override = default;

    std::string get_app_name() override {
        return "novel";
    }

    void *get_icon() override {
        return app_package_base::get_icon();
    }

    void *get_custom_data() override {
        return app_package_base::get_custom_data();
    }

    void *new_app() override {
        return new app_novel();
    }

    void delete_app(void *app) override {
        delete (app_novel *)app;
    }
};

#endif //MICRO_SNOW_APP_NOVEL_H
