/**
*********************************************************************
*********
* @project_name :micro_snow
* @file : app_novel.cpp
* @author : ruixuezhao890
* @brief : None
* @attention : None
* @date : 2024/12/30 
*********************************************************************
*********
*/


#include "app_novel.h"
#include "ep_lib.h"

app_novel_widget * app_novel::get_app_novel_ui_widget(){
    return (app_novel_widget *)app_ui_->get_screen_widget();
}

app_novel::app_novel() {

}
app_novel::~app_novel(){

}
void *app_novel::ui_create() {
    return new app_novel_ui();
}

void app_novel::on_create() {
    widget_=get_app_novel_ui_widget();
}

void app_novel::on_resume() {
    ep_string_control::ep_new_line_printf("resume");
}

void app_novel::on_running() {
    ep_string_control::ep_new_line_printf("novel_on_running");
    ep_delay_control::ep_delay_ms(500);
}

void app_novel::on_running_background_running() {
    app_base::on_running_background_running();
}

void app_novel::on_pause() {
    app_base::on_pause();
}

void app_novel::on_destroy() {
    app_base::on_destroy();
}

void app_novel_ui::screen_init_function() {
    auto btn= lv_btn_create(screen_obj_t);
    auto label= lv_label_create(btn);
    lv_label_set_text(label,"app_novel test");
    lv_obj_center(btn);
    lv_obj_add_event_cb(btn,[](lv_event_t* event){
        auto code= lv_event_get_code(event);
        if (code==LV_EVENT_CLICKED){
            static int cnt=0;
            cnt++;
            ep_string_control::ep_new_line_printf("cnt nums is {}",cnt);
        }
    },LV_EVENT_CLICKED, nullptr);
}