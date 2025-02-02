/**
*********************************************************************
*********
* @project_name :micro_snow
* @file : fs.cpp
* @author : ruixuezhao890
* @brief : None
* @attention : None
* @date : 2025/1/3 
*********************************************************************
*********
*/
#include "device/filesystem/fs_device.h"
#include "ep_lib.h"
#include "SD.h"
void fs_device::re_init() {
    sd_spi_ = new SPIClass(HSPI);
    pinMode(SD_CS, OUTPUT);
    digitalWrite(SD_CS, HIGH);
    sd_spi_->begin(SD_SCLK, SD_MISO, SD_MOSI, SD_CS);
    if (!SD.begin(SD_CS, *sd_spi_)) {
        ep_string_control::ep_new_line_printf("sd card init failed");
    }
    uint8_t cardType = SD.cardType();
    if (cardType == CARD_NONE) {
        ep_string_control::ep_printf("No SD card attached\r\n");
        return;
    } else {
        ep_string_control::ep_printf("SD Card Type: ");
        if (cardType == CARD_MMC) {
            ep_string_control::ep_printf("MMC\r\n");
        } else if (cardType == CARD_SD) {
            ep_string_control::ep_printf("SDSC\r\n");
        } else if (cardType == CARD_SDHC) {
            ep_string_control::ep_printf("SDHC\r\n");
        } else {
            ep_string_control::ep_printf("UNKNOWN\r\n");
        }
    }
    uint64_t totalBytes = SD.totalBytes();
    uint64_t usedBytes = SD.usedBytes();
    auto SDCard_Size = totalBytes/(1024*1024);
    ep_string_control::ep_printf("Total space: {}\n", totalBytes);
    ep_string_control::ep_printf("Used space:  {} \n", usedBytes);
    ep_string_control::ep_printf("Free space:  {} \n", totalBytes - usedBytes);
}

fs_device::~fs_device() {
    delete sd_spi_;
    sd_spi_ = nullptr;
}
