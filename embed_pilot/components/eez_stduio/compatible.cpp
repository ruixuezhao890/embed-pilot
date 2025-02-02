/**
*********************************************************************
*********
* @project_name :micro_snow
* @file : compatible.cpp
* @author : ruixuezhao890
* @brief : None
* @attention : None
* @date : 2025/1/23 
*********************************************************************
*********
*/


#include "compatible.hpp"
#include "eez-flow.h"
static lv_obj_t *getLvglObjectFromIndex(int32_t index) {
    if (index == -1) {
        return 0;
    }
    return ((lv_obj_t **)&objects)[index];
}

void loadScreen(enum ScreensEnum screenId) {
    auto currentScreen = screenId - 1;
    g_currentScreen=currentScreen;
    lv_obj_t *screen = getLvglObjectFromIndex(currentScreen);
    lv_scr_load_anim(screen, LV_SCR_LOAD_ANIM_FADE_IN, 200, 0, false);
}