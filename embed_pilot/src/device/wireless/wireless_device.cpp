/**
*********************************************************************
*********
* @project_name :micro_snow
* @file : wireless_device.cpp
* @author : ruixuezhao890
* @brief : None
* @attention : None
* @date : 2025/1/1 
*********************************************************************
*********
*/
#include "device/wireless/wireless_device.h"

bool wireless_device::isWifiConnection() const {
    return wifi_connection_;
}

void wireless_device::setWifiConnection(bool t) {
    wifi_connection_=t;
}

bool wireless_device::isScanFinish() const {
    return scan_finish_;
}

static void wifiTask(void *parameter) {
    auto device=static_cast<wireless_device *>(parameter);

    for (; ;) {
        if (device->status()!=WL_CONNECTED){
            device->setWifiConnection(false);
            ep_string_control::ep_new_line_printf("wifi connecting");
            device->begin(device->get_ssid(),device->get_password());
            while(device->status()!=WL_CONNECTED){
                ep_info_log(".")
                ep_delay_control::ep_delay_os(1000);
            }
        }
        ep_string_control::ep_printf("\n");
        ep_string_control::ep_printf("wifi connected\n");
        ep_string_control::ep_printf("ip address: {}",device->localIP());
        device->setWifiConnection(true);
        ep_hw_abstract::hardware_abstract::calibration_time();//校准时间
        vTaskDelete(device->wifi_task);
    }

}

void wireless_device::wifi_connect(const char *ssid, const char *password) {\
    this->disconnect();
    this->ssid=ssid;this->password=password;
    xTaskCreate(
            wifiTask,          // 任务函数
            "WiFi Task",       // 任务名称
            10000,             // 任务堆栈大小
            this,              // 传递给任务的参数
            4,                 // 任务优先级
            &wifi_task             // 任务句柄
    );
}