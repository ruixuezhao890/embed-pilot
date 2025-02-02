/**
*********************************************************************
*********
* @project_name :micro_snow
* @file : app_music.h
* @author : ruixuezhao890
* @brief : None
* @attention : None
* @date : 2024/12/30 
*********************************************************************
*********
*/


#ifndef MICRO_SNOW_APP_MUSIC_H
#define MICRO_SNOW_APP_MUSIC_H
#include "application/app_blueprint/app.h"
LV_IMG_DECLARE(music_icon)

struct app_music_widget{

};

class app_music_ui:public ep_application::app_ui_base{
protected:
    void screen_init_function() override;
    app_music_widget widget;
public:
    void * get_screen_widget() override{
        return (void *)&widget;
    }
};
class app_music : public ep_application::app_base{
    app_music_widget * widget_{};
public:
    app_music_widget * get_app_music_ui_widget();

    app_music();

    ~app_music() override;

    void *ui_create() override;

    void on_create() override;

    void on_resume() override;

    void on_running() override;

    void on_running_background_running() override;

    void on_pause() override;

    void on_destroy() override;
};

class app_music_packager:public ep_application::app_package_base{
public:
    ~app_music_packager() override = default;

    std::string get_app_name() override {
        return "music";
    }

    void *get_icon() override {
        return (void *)&music_icon;
    }

    void *get_custom_data() override {
        return app_package_base::get_custom_data();
    }

    void *new_app() override {
        return new app_music();
    }

    void delete_app(void *app) override {
        delete (app_music *)app;
    }
};

#endif //MICRO_SNOW_APP_MUSIC_H
