/**
*********************************************************************
*********
* @project_name :micro_snow
* @file : fs_micro_snow.hpp
* @author : ruixuezhao890
* @brief : None
* @attention : None
* @date : 2025/1/3 
*********************************************************************
*********
*/


#ifndef MICRO_SNOW_FS_HPP
#define MICRO_SNOW_FS_HPP
#include "ep_config.h"
#ifdef MICRO_SNOW

#define SD_CS     21        //                SD_D3:  21
#define SD_MISO   16        // TFT_MISO:46    SD_D0:  16
#define SD_MOSI   17        // TFT_MOSI:45    SD_CMD: 17
#define SD_SCLK   14        // TFT_SCLK:40    SD_SCK: 14
#define SD_D1     -1        //                SD_D1:  18
#define SD_D2     -1        //                SD_D2:  15

#include <SPI.h>

class fs_device{
    SPIClass * sd_spi_;
public:
    ~fs_device();
    void re_init();
};
#endif
#endif //MICRO_SNOW_FS_MICRO_SNOW_HPP
