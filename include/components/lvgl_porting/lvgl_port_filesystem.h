/**
*********************************************************************
*********
* @project_name :embed_pilot
* @file : lvgl_port_filesystem.h
* @author : ruixuezhao890
* @brief : None
* @attention : None
* @date : 2024/12/24 
*********************************************************************
*********
*/


#ifndef EMBED_PILOT_LVGL_PORT_FILESYSTEM_H
#define EMBED_PILOT_LVGL_PORT_FILESYSTEM_H

#include "lv_conf_internal.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 * GLOBAL PROTOTYPES
 **********************/

#if LV_USE_FS_FATFS != '\0'
void lv_filesystem_fatfs_init();
#endif

#if LV_USE_FS_STDIO != '\0'
void lv_filesystem_stdio_init(void);
#endif

#if LV_USE_FS_POSIX != '\0'
void lv_filesystem_posix_init(void);
#endif

#if LV_USE_FS_WIN32 != '\0'
void lv_filesystem_win32_init(void);
#endif

/**********************
 *      MACROS
 **********************/
#endif //EMBED_PILOT_LVGL_PORT_FILESYSTEM_H
