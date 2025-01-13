/**
*********************************************************************
*********
* @project_name :micro_snow
* @file : weather_service.cpp
* @author : ruixuezhao890
* @brief : None
* @attention : None
* @date : 2025/1/10 
*********************************************************************
*********
*/
#include "../app_desk.h"
#include "ep_lib.h"
#include <ArduinoJson.h>
#include <HTTPClient.h>
#define LOG_TAG "weather_service"
static const std::string api="SH2FiwxUMouRF2EJZ";
static std::string weather_string;
static std::string city_string;
static int update_flag=0;

namespace public_search_weather_api {
    std::string get_url(const std::string &city) {
        std::string url_xinzhi = "https://api.seniverse.com/v3/weather/now.json?key=";//心知天气API接口网址
        url_xinzhi += api;
        url_xinzhi += "&location=";
        url_xinzhi += city_string;
        url_xinzhi += "&language=zh-Hans&unit=c";
        return url_xinzhi;
    }
}


static void process_weather_data(lv_timer_t* timer) {
    auto url = public_search_weather_api::get_url(city_string);
    HTTPClient http;

    http.begin(url.c_str());

    int httpCode = http.GET();
    if (httpCode <= 0) {
        ep_error_log("HTTP GET failed with error: {}", http.errorToString(httpCode).c_str());
        http.end();
        return;
    }

    if (httpCode != HTTP_CODE_OK) {
        timer->period=3000;
        ep_error_log("HTTP GET failed with code: {}", httpCode);
        http.end();
        return;
    }

    // 获取响应体
    String response = http.getString();

    JsonDocument doc;

    // 反序列化 JSON
    DeserializationError error = deserializeJson(doc, response);
    if (error) {
        ep_error_log("deserializeJson() failed: {}", error.c_str());
        if(timer){
            timer->period = 3000;
        }
        http.end();
        return;
    }

    // 从 JSON 文档中提取天气信息
    weather_string = doc["results"][0]["now"]["text"].as<std::string>();
    auto city_string_ = doc["results"][0]["location"]["name"].as<std::string>();

//    ep_info_log("Weather for city {}: {}", city_string_, weather_string);

    update_flag = 1;
    if(timer){
        timer->period = 600000;
    }

    // 结束 HTTP 连接
    http.end();
}
static void call_func(lv_timer_t* timer){
    LV_UNUSED(timer); // 确保编译器不会警告未使用参数

    int flag = 0;
    ep_hw_abstract::hardware_abstract::is_connect_wifi(flag);
    if (!flag) {
        ep_info_log("Not connected to WiFi");
        return; // 如果没有连接WiFi，直接返回
    }

    // 直接设置定时器周期为60000毫秒


    // 获取并处理天气信息
    process_weather_data(timer);
}

namespace public_search_weather_api {


    void search_weather_start() {
        int flag;
        ep_hw_abstract::hardware_abstract::is_connect_wifi(flag);
        lv_timer_t *timer = lv_timer_create(call_func, 3000, nullptr);
    }

    void set_search_city(const std::string &city) {
        city_string = city;
    }

    std::string &get_search_city() {
        return city_string;
    }

    const std::string get_weather_city() {
        return weather_string;
    }

    int &get_update_flag() {
        return update_flag;
    }
}
