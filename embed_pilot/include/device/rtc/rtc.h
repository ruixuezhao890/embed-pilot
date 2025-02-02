/**
*********************************************************************
*********
* @project_name :micro_snow
* @file : rtc_micro_snow.h
* @author : ruixuezhao890
* @brief : None
* @attention : None
* @date : 2024/12/31 
*********************************************************************
*********
*/


#ifndef MICRO_SNOW_RTC_H
#define MICRO_SNOW_RTC_H
#include "ep_lib.h"

#ifdef MICRO_SNOW
#include "Wire.h"
#include "NTPClient.h"
#include "device/wireless/wireless_device.h"
#include "SensorPCF85063.hpp"

#define PCF85063_IRQ_PIN      -1
#define RTC_I2C_SCL_PIN       10
#define RTC_I2C_SDA_PIN       11

class rtc{
    TwoWire * rtc_wire_;
    NTPClient * time_client_;
    SensorPCF85063 rtc_;
    WiFiUDP ntp_udp_;
    wireless_device * wireless_micro_snow_;
protected:
    void network_timing();
public:
    rtc();

    ~rtc();

    void re_init(wireless_device * wireless);

    void read_time(ep_hw_abstract::rtc_data_time &data);

    void calibration_time();

};
#endif
#endif //MICRO_SNOW_RTC_MICRO_SNOW_H
