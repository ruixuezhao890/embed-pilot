/**
*********************************************************************
*********
* @project_name :micro_snow
* @file : gyroscope.cpp
* @author : ruixuezhao890
* @brief : None
* @attention : None
* @date : 2024/12/31 
*********************************************************************
*********
*/
#include "device/gyroscope/gyroscope.h"
#include "ep_lib.h"

gyroscope::gyroscope() {
    re_init();
}

void gyroscope::get_imu_data_acceleration(IMUdata &data) {
    if (QMI.getDataReady()){
        if (!QMI.getAccelerometer(data.x,data.y,data.z)){
            ep_string_control::ep_new_line_printf("get acc data error");
        }
    }
}

void gyroscope::get_imu_data_gyroscope(IMUdata &data) {
    if (QMI.getDataReady()){
        if (!QMI.getGyroscope(data.x,data.y,data.z)){
            ep_string_control::ep_new_line_printf("get acc gyro error");
        }
    }
}

void gyroscope::re_init() {
    iic_gyroscope_=&Wire1;
    //Using WIRE !!
    if (!QMI.begin(*iic_gyroscope_, QMI8658_L_SLAVE_ADDRESS, GYROSCOPE_I2C_SDA_PIN, GYROSCOPE_I2C_SCL_PIN)) {
        ep_string_control::ep_printf("Failed to find QMI8658 -  Try again!\r\n");
        if (!QMI.begin(*iic_gyroscope_, QMI8658_L_SLAVE_ADDRESS, GYROSCOPE_I2C_SDA_PIN, GYROSCOPE_I2C_SCL_PIN)) {
            ep_string_control::ep_printf("Failed to find QMI8658 -  Try again!\r\n");
            while (1) {
                printf("Failed to find QMI8658!!!\r\n");
                ep_delay_control::ep_delay_os(1000);
            }
        }
    }
//  printf("Device ID: %x\r\n",QMI.getChipID());    // Get chip id

    QMI.configAccelerometer(
            SensorQMI8658::ACC_RANGE_4G,      // ACC_RANGE_2G / ACC_RANGE_4G / ACC_RANGE_8G / ACC_RANGE_16G
            SensorQMI8658::ACC_ODR_1000Hz,    // ACC_ODR_1000H / ACC_ODR_500Hz / ACC_ODR_250Hz / ACC_ODR_125Hz / ACC_ODR_62_5Hz / ACC_ODR_31_25Hz / ACC_ODR_LOWPOWER_128Hz / ACC_ODR_LOWPOWER_21Hz / ACC_ODR_LOWPOWER_11Hz / ACC_ODR_LOWPOWER_3Hz
            SensorQMI8658::LPF_MODE_0        //LPF_MODE_0 (2.66% of ODR) / LPF_MODE_1 (3.63% of ODR) / LPF_MODE_2 (5.39% of ODR) / LPF_MODE_3 (13.37% of ODR)
    );                            // selfTest enable true
    QMI.configGyroscope(
            SensorQMI8658::GYR_RANGE_64DPS,   // GYR_RANGE_16DPS / GYR_RANGE_32DPS / GYR_RANGE_64DPS / GYR_RANGE_128DPS / GYR_RANGE_256DPS / GYR_RANGE_512DPS / GYR_RANGE_1024DPS
            SensorQMI8658::GYR_ODR_896_8Hz,   // GYR_ODR_7174_4Hz / GYR_ODR_3587_2Hz / GYR_ODR_1793_6Hz / GYR_ODR_896_8Hz / GYR_ODR_448_4Hz / GYR_ODR_224_2Hz / GYR_ODR_112_1Hz / GYR_ODR_56_05Hz / GYR_ODR_28_025H
            SensorQMI8658::LPF_MODE_3        // LPF_MODE_0 (2.66% of ODR) / LPF_MODE_1 (3.63% of ODR) / LPF_MODE_2 (5.39% of ODR) / LPF_MODE_3 (13.37% of ODR)
    );                            // selfTest enable true


    // In 6DOF mode (accelerometer and gyroscope are both enabled),
    // the output data rate is derived from the nature frequency of gyroscope
    QMI.enableGyroscope();
    QMI.enableAccelerometer();

    QMI.dumpCtrlRegister();               // printf register configuration information
    ep_string_control::ep_printf("Read data now...\r\n");
}

gyroscope::~gyroscope() {
//    delete iic_gyroscope_;
    iic_gyroscope_= nullptr;
}

void gyroscope::exmaple() {
    IMUdata  udata;
    IMUdata  udata1;
    get_imu_data_acceleration(udata);
    get_imu_data_acceleration(udata1);

    ep_string_control::ep_new_line_printf("acc x:{:.2},y:{:.2},z:{:.2}",udata.x,udata.y,udata.z);

//        Serial.print(udata.x);
//        Serial.print(udata.y);
//        Serial.print(udata.z);
//        Serial.println();
//        Serial.print(udata1.x);
//        Serial.print(udata1.y);
//        Serial.print(udata1.z);

}
