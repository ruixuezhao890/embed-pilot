#include <string.h>

#include "screens.h"
#include "images.h"
#include "fonts.h"
#include "actions.h"
#include "vars.h"
#include "styles.h"
#include "ui.h"

#include <string.h>

objects_t objects;
lv_obj_t *tick_value_change_obj;

static void event_handler_cb_main_app_panel(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    
    if (event == LV_EVENT_SCREEN_LOADED) {
        e->user_data = (void *)0;
        flowPropagateValueLVGLEvent(flowState, 2, 0, e);
    }
}

static void event_handler_cb_main_app_icon(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    
    if (event == LV_EVENT_CLICKED) {
        e->user_data = (void *)0;
        flowPropagateValueLVGLEvent(flowState, 3, 0, e);
    }
}

static void event_handler_cb_main_app_selector_panel(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    
    if (event == LV_EVENT_SCREEN_LOADED) {
        e->user_data = (void *)0;
        action_scroll_finsh_callback(e);
    }
}

static void event_handler_cb_main_time_weather_panel(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    
    if (event == LV_EVENT_SCREEN_LOADED) {
        e->user_data = (void *)0;
        flowPropagateValueLVGLEvent(flowState, 13, 0, e);
    }
}

static void event_handler_cb_music_music_player_mode_label(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    
    if (event == LV_EVENT_CLICKED) {
        e->user_data = (void *)0;
        action_change_player_mode(e);
    }
}

static void event_handler_cb_music_music_next(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    
    if (event == LV_EVENT_CLICKED) {
        e->user_data = (void *)0;
        action_next_music_callback(e);
    }
}

static void event_handler_cb_music_music_puase(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    
    if (event == LV_EVENT_CLICKED) {
        e->user_data = (void *)0;
        action_pause_music_paly(e);
    }
}

static void event_handler_cb_music_music_pre(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    
    if (event == LV_EVENT_CLICKED) {
        e->user_data = (void *)0;
        action_pre_music_callback(e);
    }
}

static void event_handler_cb_music_music_name_list(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    
    if (event == LV_EVENT_CLICKED) {
        e->user_data = (void *)0;
        action_create_music_name_list_callback(e);
    }
}

static void event_handler_cb_menu_obj0(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    
    if (event == LV_EVENT_CLICKED) {
        e->user_data = (void *)0;
        flowPropagateValueLVGLEvent(flowState, 0, 0, e);
    }
}

void create_screen_main() {
    void *flowState = getFlowState(0, 0);
    lv_obj_t *obj = lv_obj_create(0);
    objects.main = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 240, 320);
    {
        lv_obj_t *parent_obj = obj;
        {
            // main_container
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.main_container = obj;
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 240, 320);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
            lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // app_panel
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    objects.app_panel = obj;
                    lv_obj_set_pos(obj, 10, 170);
                    lv_obj_set_size(obj, 220, 146);
                    lv_obj_add_event_cb(obj, event_handler_cb_main_app_panel, LV_EVENT_ALL, flowState);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                    lv_obj_set_style_border_color(obj, lv_color_hex(0xff1a1818), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_width(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_radius(obj, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // app_icon
                            lv_obj_t *obj = lv_imgbtn_create(parent_obj);
                            objects.app_icon = obj;
                            lv_obj_set_pos(obj, -2, 36);
                            lv_obj_set_size(obj, 60, 60);
                            lv_obj_add_event_cb(obj, event_handler_cb_main_app_icon, LV_EVENT_ALL, flowState);
                            lv_obj_set_style_border_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_border_width(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_radius(obj, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
                        }
                        {
                            // app_selector_panel
                            lv_obj_t *obj = lv_obj_create(parent_obj);
                            objects.app_selector_panel = obj;
                            lv_obj_set_pos(obj, 80, -8);
                            lv_obj_set_size(obj, 120, 135);
                            lv_obj_add_event_cb(obj, event_handler_cb_main_app_selector_panel, LV_EVENT_ALL, flowState);
                            lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
                            lv_obj_set_scroll_snap_x(obj, LV_DIR_VER);
                            lv_obj_set_scroll_snap_y(obj, LV_SCROLL_SNAP_CENTER);
                            lv_obj_set_style_border_color(obj, lv_color_hex(0xff3d2e2e), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_border_width(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_radius(obj, 15, LV_PART_MAIN | LV_STATE_DEFAULT);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    lv_obj_t *obj = lv_btn_create(parent_obj);
                                    lv_obj_set_pos(obj, -4, 192);
                                    lv_obj_set_size(obj, 100, 50);
                                    {
                                        lv_obj_t *parent_obj = obj;
                                        {
                                            lv_obj_t *obj = lv_label_create(parent_obj);
                                            lv_obj_set_pos(obj, 0, 0);
                                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                            lv_label_set_text(obj, "Button");
                                            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                        }
                                    }
                                }
                                {
                                    lv_obj_t *obj = lv_btn_create(parent_obj);
                                    lv_obj_set_pos(obj, -4, -4);
                                    lv_obj_set_size(obj, 100, 50);
                                    {
                                        lv_obj_t *parent_obj = obj;
                                        {
                                            lv_obj_t *obj = lv_label_create(parent_obj);
                                            lv_obj_set_pos(obj, 0, 0);
                                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                            lv_label_set_text(obj, "Button");
                                            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                        }
                                    }
                                }
                                {
                                    lv_obj_t *obj = lv_btn_create(parent_obj);
                                    lv_obj_set_pos(obj, -4, 127);
                                    lv_obj_set_size(obj, 100, 50);
                                    {
                                        lv_obj_t *parent_obj = obj;
                                        {
                                            lv_obj_t *obj = lv_label_create(parent_obj);
                                            lv_obj_set_pos(obj, 0, 0);
                                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                            lv_label_set_text(obj, "Button");
                                            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                        }
                                    }
                                }
                                {
                                    lv_obj_t *obj = lv_btn_create(parent_obj);
                                    lv_obj_set_pos(obj, -4, 61);
                                    lv_obj_set_size(obj, 100, 50);
                                    {
                                        lv_obj_t *parent_obj = obj;
                                        {
                                            lv_obj_t *obj = lv_label_create(parent_obj);
                                            lv_obj_set_pos(obj, 0, 0);
                                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                            lv_label_set_text(obj, "Button");
                                            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
                {
                    // time_weather_panel
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    objects.time_weather_panel = obj;
                    lv_obj_set_pos(obj, 10, 10);
                    lv_obj_set_size(obj, 220, 150);
                    lv_obj_add_event_cb(obj, event_handler_cb_main_time_weather_panel, LV_EVENT_ALL, flowState);
                    lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
                    lv_obj_set_style_radius(obj, 15, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_width(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_color(obj, lv_color_hex(0xff3d2e2e), LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // wifi_label
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.wifi_label = obj;
                            lv_obj_set_pos(obj, 1, 105);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_label_set_text(obj, "");
                            lv_obj_add_flag(obj, LV_OBJ_FLAG_HIDDEN);
                        }
                        {
                            // week_label
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.week_label = obj;
                            lv_obj_set_pos(obj, 104, 105);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_label_set_text(obj, "wednesday");
                        }
                        {
                            // date_label
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.date_label = obj;
                            lv_obj_set_pos(obj, 111, 78);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_label_set_text(obj, "2025/1/25");
                        }
                        {
                            // weather_img
                            lv_obj_t *obj = lv_img_create(parent_obj);
                            objects.weather_img = obj;
                            lv_obj_set_pos(obj, 115, 0);
                            lv_obj_set_size(obj, 60, 60);
                            lv_obj_set_style_border_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_border_width(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_radius(obj, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
                        }
                        {
                            // time_min
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.time_min = obj;
                            lv_obj_set_pos(obj, 45, 48);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_label_set_text(obj, "20");
                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_28, LV_PART_MAIN | LV_STATE_DEFAULT);
                        }
                        {
                            // time_hour
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.time_hour = obj;
                            lv_obj_set_pos(obj, 2, 3);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_label_set_text(obj, "12");
                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_28, LV_PART_MAIN | LV_STATE_DEFAULT);
                        }
                        {
                            // buletooth_label
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.buletooth_label = obj;
                            lv_obj_set_pos(obj, 57, 105);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_label_set_text(obj, "");
                            lv_obj_add_flag(obj, LV_OBJ_FLAG_HIDDEN);
                        }
                    }
                }
            }
        }
    }
}

void tick_screen_main() {
    void *flowState = getFlowState(0, 0);
    {
        const char *new_val = evalTextProperty(flowState, 14, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.wifi_label);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.wifi_label;
            lv_label_set_text(objects.wifi_label, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 20, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.buletooth_label);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.buletooth_label;
            lv_label_set_text(objects.buletooth_label, new_val);
            tick_value_change_obj = NULL;
        }
    }
}

void create_screen_music() {
    void *flowState = getFlowState(0, 1);
    lv_obj_t *obj = lv_obj_create(0);
    objects.music = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 240, 320);
    {
        lv_obj_t *parent_obj = obj;
        {
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.obj0 = obj;
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 240, 320);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            create_user_widget_menu(obj, getFlowState(flowState, 0), 3);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // music_player_mode_label
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.music_player_mode_label = obj;
                    lv_obj_set_pos(obj, 14, 282);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_label_set_text(obj, "");
                    lv_obj_add_event_cb(obj, event_handler_cb_music_music_player_mode_label, LV_EVENT_ALL, flowState);
                    lv_obj_add_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_20, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
                {
                    // left_time_label
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.left_time_label = obj;
                    lv_obj_set_pos(obj, 11, 223);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_label_set_text(obj, "0:00");
                }
                {
                    // music_slider
                    lv_obj_t *obj = lv_slider_create(parent_obj);
                    objects.music_slider = obj;
                    lv_obj_set_pos(obj, 24, 249);
                    lv_obj_set_size(obj, 194, 10);
                    lv_slider_set_mode(obj, LV_SLIDER_MODE_SYMMETRICAL);
                    lv_slider_set_value(obj, 25, LV_ANIM_ON);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(0xffe61aa8), LV_PART_INDICATOR | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(0xffe61aa8), LV_PART_KNOB | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(0xffc0b6b6), LV_PART_MAIN | LV_STATE_DEFAULT);
                }
                {
                    // music_next
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.music_next = obj;
                    lv_obj_set_pos(obj, 159, 279);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_label_set_text(obj, "");
                    lv_obj_add_event_cb(obj, event_handler_cb_music_music_next, LV_EVENT_ALL, flowState);
                    lv_obj_add_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_24, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
                {
                    // play_image
                    lv_obj_t *obj = lv_img_create(parent_obj);
                    objects.play_image = obj;
                    lv_obj_set_pos(obj, 40, 45);
                    lv_obj_set_size(obj, 160, 160);
                    lv_obj_set_style_radius(obj, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_outline_width(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_outline_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                }
                {
                    // title
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.title = obj;
                    lv_obj_set_pos(obj, 72, 20);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_label_set_text(obj, "music_player");
                }
                {
                    // right_time_label
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.right_time_label = obj;
                    lv_obj_set_pos(obj, 204, 223);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_label_set_text(obj, "3:00");
                }
                {
                    // music_name_label
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.music_name_label = obj;
                    lv_obj_set_pos(obj, 76, 223);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_label_set_text(obj, "music_name");
                }
                {
                    // pause_music_panel
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    objects.pause_music_panel = obj;
                    lv_obj_set_pos(obj, 99, 270);
                    lv_obj_set_size(obj, 45, 45);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                    lv_obj_set_style_radius(obj, 20, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(0xffe61aa8), LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // music_puase
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.music_puase = obj;
                            lv_obj_set_pos(obj, -1, -3);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_label_set_text(obj, "");
                            lv_obj_add_event_cb(obj, event_handler_cb_music_music_puase, LV_EVENT_ALL, flowState);
                            lv_obj_add_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_20, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                        }
                    }
                }
                {
                    // music_pre
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.music_pre = obj;
                    lv_obj_set_pos(obj, 64, 279);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_label_set_text(obj, "");
                    lv_obj_add_event_cb(obj, event_handler_cb_music_music_pre, LV_EVENT_ALL, flowState);
                    lv_obj_add_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_24, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
            }
        }
        {
            // music_name_list
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.music_name_list = obj;
            lv_obj_set_pos(obj, 208, 282);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "");
            lv_obj_add_event_cb(obj, event_handler_cb_music_music_name_list, LV_EVENT_ALL, flowState);
            lv_obj_add_flag(obj, LV_OBJ_FLAG_CLICKABLE);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_20, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
    }
}

void tick_screen_music() {
    void *flowState = getFlowState(0, 1);
    tick_user_widget_menu(getFlowState(flowState, 0), 3);
    {
        const char *new_val = evalTextProperty(flowState, 2, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.music_player_mode_label);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.music_player_mode_label;
            lv_label_set_text(objects.music_player_mode_label, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 5, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.music_next);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.music_next;
            lv_label_set_text(objects.music_next, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 11, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.music_puase);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.music_puase;
            lv_label_set_text(objects.music_puase, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 12, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.music_pre);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.music_pre;
            lv_label_set_text(objects.music_pre, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 13, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.music_name_list);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.music_name_list;
            lv_label_set_text(objects.music_name_list, new_val);
            tick_value_change_obj = NULL;
        }
    }
}

void create_user_widget_menu(lv_obj_t *parent_obj, void *flowState, int startWidgetIndex) {
    lv_obj_t *obj = parent_obj;
    {
        lv_obj_t *parent_obj = obj;
        {
            lv_obj_t *obj = lv_obj_create(parent_obj);
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 240, 320);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    ((lv_obj_t **)&objects)[startWidgetIndex + 0] = obj;
                    lv_obj_set_pos(obj, 15, 15);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_label_set_text(obj, "");
                    lv_obj_add_event_cb(obj, event_handler_cb_menu_obj0, LV_EVENT_ALL, flowState);
                    lv_obj_add_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_18, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
            }
        }
    }
}

void tick_user_widget_menu(void *flowState, int startWidgetIndex) {
    {
        const char *new_val = evalTextProperty(flowState, 0, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(((lv_obj_t **)&objects)[startWidgetIndex + 0]);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = ((lv_obj_t **)&objects)[startWidgetIndex + 0];
            lv_label_set_text(((lv_obj_t **)&objects)[startWidgetIndex + 0], new_val);
            tick_value_change_obj = NULL;
        }
    }
}


extern void add_style(lv_obj_t *obj, int32_t styleIndex);
extern void remove_style(lv_obj_t *obj, int32_t styleIndex);

static const char *screen_names[] = { "Main", "music" };
static const char *object_names[] = { "main", "music", "obj0", "obj0__obj0", "app_panel", "app_icon", "app_selector_panel", "time_weather_panel", "music_player_mode_label", "music_next", "music_puase", "music_pre", "music_name_list", "main_container", "wifi_label", "week_label", "date_label", "weather_img", "time_min", "time_hour", "buletooth_label", "left_time_label", "music_slider", "play_image", "title", "right_time_label", "music_name_label", "pause_music_panel" };
static const char *style_names[] = { "slider_style", "button_style" };

void create_screens() {
    eez_flow_init_styles(add_style, remove_style);
    
    eez_flow_init_screen_names(screen_names, sizeof(screen_names) / sizeof(const char *));
    eez_flow_init_object_names(object_names, sizeof(object_names) / sizeof(const char *));
    eez_flow_init_style_names(style_names, sizeof(style_names) / sizeof(const char *));
    
    lv_disp_t *dispp = lv_disp_get_default();
    lv_theme_t *theme = lv_theme_default_init(dispp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED), false, LV_FONT_DEFAULT);
    lv_disp_set_theme(dispp, theme);
    
    create_screen_main();
    create_screen_music();
}

typedef void (*tick_screen_func_t)();

tick_screen_func_t tick_screen_funcs[] = {
    tick_screen_main,
    tick_screen_music,
    0,
};

void tick_screen(int screen_index) {
    tick_screen_funcs[screen_index]();
}
