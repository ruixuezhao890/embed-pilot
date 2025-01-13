/**
*********************************************************************
*********
* @project_name :micro_snow
* @file : hardware_layer_abstract.h
* @author : ruixuezhao890
* @brief : None
* @attention : None
* @date : 2024/12/24 
*********************************************************************
*********
*/


#ifndef MICRO_SNOW_HARDWARE_LAYER_ABSTRACT_H
#define MICRO_SNOW_HARDWARE_LAYER_ABSTRACT_H
#include "ep_lib.h"
//#include "components/libraries/one_button/OneButton.h"
class OneButton;
namespace ep_hw_abstract{
    struct imu_data{
        float x;
        float y;
        float z;
    };
    struct rtc_data_time{
        uint16_t year;
        uint8_t  month;
        uint8_t  day;
        uint8_t  hour;
        uint8_t  minute;
        uint8_t  second;
    };





    class hardware_abstract{
    private:
       static hardware_abstract * hw_abstract_instance_;

    protected:
        imu_data imu_data_acceleration{};

        imu_data imu_data_gyroscope{};

        hardware_abstract()=default;

       virtual ~hardware_abstract()= default;

    public:
        hardware_abstract(const hardware_abstract&)=delete;

        hardware_abstract& operator=(const hardware_abstract&)=delete;

        static hardware_abstract * get_hw_instance();

        static void release_hw_instance();

        static void inject_instance(ep_hw_abstract::hardware_abstract* inject);

        virtual std::string type(){return "base";}

        virtual void init(){};

        static void update_data();
        virtual void Update_data();

        static void file_system_init();
        virtual void File_system_init();

        static void display(lv_disp_drv_t * disp_drv,const lv_area_t * area,lv_color_t * color_p);
        virtual void Display(lv_disp_drv_t * disp_drv,const lv_area_t * area,lv_color_t * color_p);

        static void touch(lv_indev_drv_t * indev_drv,lv_indev_data_t * data);
        virtual void Touch(lv_indev_drv_t * indev_drv,lv_indev_data_t * data);

        static void get_imu_data_acceleration(imu_data& data );
        virtual void Get_imu_data_acceleration(imu_data& data);

        static void get_imu_data_gyroscope(imu_data& data);
        virtual void Get_imu_data_gyroscope(imu_data& data);

        static void get_rtc_data_time(rtc_data_time& data);
        virtual void Get_rtc_data_time(rtc_data_time& data);

        static void calibration_time();
        virtual void Calibration_time();

        static uint16_t get_battery_electric_quantity();
        virtual uint16_t Get_battery_electric_quantity();

        static void add_one_button(OneButton& config);
        virtual void Add_one_button(OneButton& config);

        static void deep_sleep();
        virtual void Deep_sleep();

        static void power_off();
        virtual void Power_off();

        static void restart();
        virtual void Restart();

        static void connect_wifi(const char * ssid,const char * password);
        virtual void Connect_wifi(const char * ssid,const char * password);

        static  void is_connect_wifi(int& flag);
        virtual void Is_connect_wifi(int& flag);
    };
}
#endif //MICRO_SNOW_HARDWARE_LAYER_ABSTRACT_H
