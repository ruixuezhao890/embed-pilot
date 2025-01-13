/**
*********************************************************************
*********
* @project_name :micro_snow
* @file : app_blueprint.h
* @author : ruixuezhao890
* @brief : None
* @attention : None
* @date : 2024/12/24 
*********************************************************************
*********
*/


#ifndef MICRO_SNOW_APP_INSTALL_H
#define MICRO_SNOW_APP_INSTALL_H
#include "ep_lib.h"
#include "../app_sys/app_desk/app_desk.h"
#include "../app_user/app_music/app_music.h"
#include "../app_user/app_novel/app_novel.h"
#include "../app_user/app_demo/app_demo.h"
/* Header files locator(Don't remove) */

void ep_install_app_function(embed_pilot::ep_activate * ep_activate){
    bool ret= false;
    	ret=ep_activate->install_app(new app_desk_packager());
		ret=ep_activate->install_app(new app_music_packager());
		ret=ep_activate->install_app(new app_novel_packager());
		ret=ep_activate->install_app(new app_demo_packager());
	/* Install app locator(Don't remove) */
    if (!ret){
        ep_string_control::ep_printf("install error");
    }


}
#endif //MICRO_SNOW_APP_INSTALL_H
