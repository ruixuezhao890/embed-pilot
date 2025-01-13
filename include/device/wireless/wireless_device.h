/**
*********************************************************************
*********
* @project_name :micro_snow
* @file : wireless_micro_snow.h
* @author : ruixuezhao890
* @brief : None
* @attention : None
* @date : 2025/1/1 
*********************************************************************
*********
*/


#ifndef MICRO_SNOW_WIRELESS_H
#define MICRO_SNOW_WIRELESS_H
#include "ep_lib.h"

#ifdef MICRO_SNOW
#include "WiFi.h"
#include "BLEDevice.h"

class wireless_device:public WiFiClass{
public:

    bool wifi_connection_{false};
    bool scan_finish_{false};

    const char * ssid;

    const char * password;

    TaskHandle_t wifi_task;

    const char *get_ssid(){
        return ssid;
    }

    const char *get_password(){
        return password;
    }

    bool isWifiConnection() const;

    void setWifiConnection(bool t) ;

    bool isScanFinish() const;

    void wifi_connect(const char * ssid,const char * password);

    void wifi_scan();

    void ble_scan();

    int wifi_scan_number();

    int ble_scan_number();
};

#endif
#endif //MICRO_SNOW_WIRELESS_MICRO_SNOW_H
