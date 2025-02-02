/**
*********************************************************************
*********
* @project_name :micro_snow
* @file : gyroscope_micro_snow.h
* @author : ruixuezhao890
* @brief : None
* @attention : None
* @date : 2024/12/31 
*********************************************************************
*********
*/


#ifndef MICRO_SNOW_GYROSCOPE_H
#define MICRO_SNOW_GYROSCOPE_H
#include "ep_config.h"
#ifdef MICRO_SNOW

#define GYROSCOPE_I2C_SCL_PIN       10
#define GYROSCOPE_I2C_SDA_PIN       11

#include "SensorQMI8658.hpp"
class gyroscope{

    SensorQMI8658 QMI;
    TwoWire * iic_gyroscope_;

public:
    gyroscope();

    ~gyroscope();

    void re_init();

    void get_imu_data_acceleration(IMUdata & data);

    void get_imu_data_gyroscope(IMUdata & data);

    void exmaple();
};

#endif
#endif //MICRO_SNOW_GYROSCOPE_MICRO_SNOW_H
