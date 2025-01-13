/**
*********************************************************************
*********
* @project_name :micro_snow
* @file : app_template.cpp
* @author : ruixuezhao890
* @brief : None
* @attention : None
* @date : 2024/12/30 
*********************************************************************
*********
*/


#include "app_template.h"
#include "ep_lib.h"

app_template_widget * app_template::get_app_template_ui_widget(){
    return (app_template_widget *)app_ui_->get_screen_widget();
}

app_template_ui * app_template::get_app_desk_ui() {
    return (app_template_ui *)app_ui_;
}

app_template::app_template() {

}
app_template::~app_template(){

}
void *app_template::ui_create() {
    return new app_template_ui();
}

// * 如果想控制创建应用时是否需要清除上一个应用的控件，true则是需要否则反之
void app_template::set_whether_the_previous_screen_is_cleared() {
    app_ui_->set_screen_init_function(true);
}

void app_template::on_create() {
    widget_=get_app_template_ui_widget();
    app_template_ui_=get_app_desk_ui();
}

void app_template::on_resume() {
    ep_string_control::ep_new_line_printf("resume");
}

void app_template::on_running() {
    ep_string_control::ep_new_line_printf("template_on_running");
    ep_delay_control::ep_delay_ms(500);
}

void app_template::on_running_background_running() {
    app_base::on_running_background_running();
}

void app_template::on_pause() {
    app_base::on_pause();
}

void app_template::on_destroy() {
    app_base::on_destroy();
}

void app_template_ui::screen_init_function() {
    auto btn= lv_btn_create(screen_obj_t);
    auto label= lv_label_create(btn);
    lv_label_set_text(label,"app_template test");
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