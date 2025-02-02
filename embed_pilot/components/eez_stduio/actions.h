#ifndef EEZ_LVGL_UI_EVENTS_H
#define EEZ_LVGL_UI_EVENTS_H

#include <lvgl.h>

#ifdef __cplusplus
extern "C" {
#endif

extern void action_open_app_callback(lv_event_t * e);
extern void action_scroll_finsh_callback(lv_event_t * e);
extern void action_create_music_name_list_callback(lv_event_t * e);
extern void action_change_player_mode(lv_event_t * e);
extern void action_pre_music_callback(lv_event_t * e);
extern void action_next_music_callback(lv_event_t * e);
extern void action_pause_music_paly(lv_event_t * e);


#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_EVENTS_H*/