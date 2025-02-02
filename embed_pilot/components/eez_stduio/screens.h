#ifndef EEZ_LVGL_UI_SCREENS_H
#define EEZ_LVGL_UI_SCREENS_H

#include <lvgl.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _objects_t {
    lv_obj_t *main;
    lv_obj_t *music;
    lv_obj_t *obj0;
    lv_obj_t *obj0__obj0;
    lv_obj_t *app_panel;
    lv_obj_t *app_icon;
    lv_obj_t *app_selector_panel;
    lv_obj_t *time_weather_panel;
    lv_obj_t *music_player_mode_label;
    lv_obj_t *music_next;
    lv_obj_t *music_puase;
    lv_obj_t *music_pre;
    lv_obj_t *music_name_list;
    lv_obj_t *main_container;
    lv_obj_t *wifi_label;
    lv_obj_t *week_label;
    lv_obj_t *date_label;
    lv_obj_t *weather_img;
    lv_obj_t *time_min;
    lv_obj_t *time_hour;
    lv_obj_t *buletooth_label;
    lv_obj_t *left_time_label;
    lv_obj_t *music_slider;
    lv_obj_t *play_image;
    lv_obj_t *title;
    lv_obj_t *right_time_label;
    lv_obj_t *music_name_label;
    lv_obj_t *pause_music_panel;
} objects_t;

extern objects_t objects;

enum ScreensEnum {
    SCREEN_ID_MAIN = 1,
    SCREEN_ID_MUSIC = 2,
};

void create_screen_main();
void tick_screen_main();

void create_screen_music();
void tick_screen_music();

void create_user_widget_menu(lv_obj_t *parent_obj, void *flowState, int startWidgetIndex);
void tick_user_widget_menu(void *flowState, int startWidgetIndex);

void create_screens();
void tick_screen(int screen_index);


#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_SCREENS_H*/