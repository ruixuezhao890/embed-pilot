/**
*********************************************************************
*********
* @project_name :micro_snow
* @file : app_desk.cpp
* @author : ruixuezhao890
* @brief : None
* @attention : None
* @date : 2024/12/30 
*********************************************************************
*********
*/


#include "app_desk.h"
#include "ep_lib.h"

app_desk_widget * app_desk::get_app_desk_ui_widget(){
    return (app_desk_widget *)app_ui_->get_screen_widget();
}

app_desk_ui * app_desk::get_app_desk_ui() {
    return (app_desk_ui *)app_ui_;
}

app_desk::app_desk() {

}
app_desk::~app_desk(){

}
void *app_desk::ui_create() {
    return new app_desk_ui();

}

void app_desk::set_whether_the_previous_screen_is_cleared() {
    app_ui_->set_screen_init_function(true);
}

void app_desk::on_create() {
    widget_=get_app_desk_ui_widget();
    app_desk_ui_=get_app_desk_ui();
    public_search_weather_api::set_search_city("永州");
    public_search_weather_api::search_weather_start();
}

void app_desk::on_resume() {;
    ep_string_control::ep_new_line_printf("resume ok");

    app_icon_draw();
}

void app_desk::on_running() {
    monitor_app_open();
    monitor_weather_changes();

}

void app_desk::on_running_background_running() {
    app_base::on_running_background_running();
}

void app_desk::on_pause() {
    app_base::on_pause();
}

void app_desk::on_destroy() {
    ep_string_control::ep_new_line_printf("app_desk on_destroy");
}

void app_desk::app_icon_draw() {
    auto embed_ptr =embed_pilot::ep_activate::get_instance();
    for (int i = 0; i <embed_ptr->get_installed_app_num() ; ++i) {
        auto app_temp_package=embed_ptr->get_installed_app_from_index(i);
        if(app_temp_package==this->app_packager_->get_app_package_address()){
            continue;
        }
        lv_obj_t * btn = lv_btn_create(widget_->app_install_panel);
        lv_obj_set_user_data(btn,(void *)app_temp_package);
        lv_obj_set_width(btn, lv_pct(100));
        lv_obj_t * label = lv_label_create(btn);
        lv_label_set_text_fmt(label, "%s", app_temp_package->get_app_name().c_str());
        lv_obj_center(label);

    }
    lv_obj_scroll_to_view(lv_obj_get_child(widget_->app_install_panel, 0), LV_ANIM_ON);
}

void app_desk::monitor_app_open() {
    if (widget_->app_click_enable){
        widget_->app_click_enable=0;
        lv_obj_add_event_cb(widget_->app_icon_img,[](lv_event_t * event){
            auto code = lv_event_get_code(event);
            if (code==LV_EVENT_CLICKED){
                auto user_data= (app_desk *)lv_event_get_user_data(event);
                auto ep =embed_pilot::ep_activate::get_instance();
                auto package=ep->get_installed_app_from_index(user_data->widget_->app_index);
//                ep_string_control::ep_new_line_printf("name:{},id:{}",package->get_app_name(),package->get_app_package_id());
                ep->create_start_app(package);
                user_data->close_app();
            }
            },LV_EVENT_CLICKED, (void*)this);
    }
}

void app_desk::monitor_weather_changes() {
    if (public_search_weather_api::get_update_flag()){
        public_search_weather_api::get_update_flag()=0;
        widget_->weather_change_flag=1;
        app_desk_ui_->monitor_weather_change(public_search_weather_api::get_weather_city());
    }
}

void app_desk_ui::screen_init_function() {
    desk_ui_init();
}