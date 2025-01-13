/**
*********************************************************************
*********
* @project_name :micro_snow
* @file : rtc.cpp
* @author : ruixuezhao890
* @brief : None
* @attention : None
* @date : 2024/12/31 
*********************************************************************
*********
*/
#include "device/rtc/rtc.h"
#include "RTC_PCF85063.h"

#include <string>

rtc::rtc() {

}

rtc::~rtc() {
    delete time_client_;
    rtc_wire_= nullptr;
    time_client_= nullptr;
}

void rtc::re_init(wireless_device * wireless) {
    rtc_wire_=&Wire1;
    wireless_micro_snow_=wireless;
    time_client_=new NTPClient(ntp_udp_, "pool.ntp.org");
    if (!rtc_.begin(*rtc_wire_, PCF85063_SLAVE_ADDRESS, I2C_SDA_PIN, I2C_SCL_PIN)) {
        ep_string_control::ep_printf("PCF85063 not found - Try again!\r\n");
        if (!rtc_.begin(*rtc_wire_, PCF85063_SLAVE_ADDRESS, I2C_SDA_PIN, I2C_SCL_PIN)) {
            ep_string_control::ep_printf("Failed to find PCF85063 !!!\r\n");
            while (1) {
                ep_string_control::ep_printf("Failed to find PCF85063 - check your wiring!\r\n");
                ep_delay_control::ep_delay_os(1000);
            }
        }
    }
}

void rtc::network_timing() {
    if (wireless_micro_snow_->status()==WL_CONNECTED){
        ep_string_control::ep_printf("WIFI connection successful, time updated!\r\n");
        time_client_->begin();
        time_client_->setTimeOffset(8 * 3600);   // Set the time zone, here use East 8 (Beijing time)
        time_client_->update();

        time_t currentTime =  time_client_->getEpochTime();
        while(currentTime < 1609459200)       // Using the current timestamp to compare with a known larger value,1609459200 is a known larger timestamp value that corresponds to January 1, 2021
        {
            time_client_->update();
            currentTime =  time_client_->getEpochTime();
        }
        // Converts the current timestamp to a tm structure
        struct tm *localTime = localtime(&currentTime);
        // Set the network time to PCF85063
        rtc_.setDateTime(localTime->tm_year - 100, localTime->tm_mon + 1, localTime->tm_mday, localTime->tm_hour, localTime->tm_min, localTime->tm_sec);
//        ep_info_log("hour:{},min:{},sec:{}",rtc_.getDateTime().hour,rtc_.getDateTime().minute,rtc_.getDateTime().second);
    }
    else{
        printf("WIFI connection failed, time not updated!\r\n");
    }
}

void rtc::read_time(ep_hw_abstract::rtc_data_time &data) {
    auto data_r=rtc_.getDateTime();
    data.year=data_r.year;
    data.month=data_r.month;
    data.day=data_r.day;
    data.hour=data_r.hour;
    data.minute=data_r.minute;
    data.second=data_r.second;
}

void rtc::calibration_time() {
    network_timing();

}


