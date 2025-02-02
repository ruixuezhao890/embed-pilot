#ifndef EEZ_LVGL_UI_STYLES_H
#define EEZ_LVGL_UI_STYLES_H

#include <lvgl.h>

#ifdef __cplusplus
extern "C" {
#endif

// Style: slider_style
lv_style_t *get_style_slider_style_MAIN_DEFAULT();
void add_style_slider_style(lv_obj_t *obj);
void remove_style_slider_style(lv_obj_t *obj);

// Style: button_style
lv_style_t *get_style_button_style_MAIN_DEFAULT();
void add_style_button_style(lv_obj_t *obj);
void remove_style_button_style(lv_obj_t *obj);



#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_STYLES_H*/