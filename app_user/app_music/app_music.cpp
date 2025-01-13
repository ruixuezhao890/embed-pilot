/**
*********************************************************************
*********
* @project_name :micro_snow
* @file : app_music.cpp
* @author : ruixuezhao890
* @brief : None
* @attention : None
* @date : 2024/12/30 
*********************************************************************
*********
*/


#include "app_music.h"
#include "ep_lib.h"

app_music_widget * app_music::get_app_music_ui_widget(){
    return (app_music_widget *)app_ui_->get_screen_widget();
}

app_music::app_music() {

}
app_music::~app_music(){

}
void *app_music::ui_create() {
    return new app_music_ui();
}

void app_music::set_whether_the_previous_screen_is_cleared() {
    app_ui_->set_screen_init_function(true);
}

void app_music::on_create() {
    widget_=get_app_music_ui_widget();
    app_ui_->set_user_date((void *)this);
}

void app_music::on_resume() {
    ep_string_control::ep_new_line_printf("resume");
}

void app_music::on_running() {
//    ep_string_control::ep_new_line_printf("music_on_running");
//    ep_delay_control::ep_delay_ms(500);
}

void app_music::on_running_background_running() {
    app_base::on_running_background_running();
}

void app_music::on_pause() {
    app_base::on_pause();
}

void app_music::on_destroy() {
    ep_string_control::ep_new_line_printf("app_music on_destroy");
}

void app_music_ui::screen_init_function() {
    auto btn= lv_btn_create(screen_obj_t);
    auto label= lv_label_create(btn);
    lv_label_set_text(label,"app_music test");
    lv_obj_center(btn);
    lv_obj_add_event_cb(btn,[](lv_event_t* event){
        auto code= lv_event_get_code(event);
        if (code==LV_EVENT_CLICKED){
            auto ep=embed_pilot::ep_activate::get_instance();
            auto user=(app_music_ui *) lv_event_get_user_data(event);
            auto app=(app_music *)user->get_user_date();
            static int cnt=0;
            cnt++;
            ep_string_control::ep_new_line_printf("cnt nums is {}",cnt);
            ep->create_start_app(ep->get_app_desk_package());
            app->close_app();
        }
    },LV_EVENT_CLICKED, (void *)this);
}