#ifndef IMU_H
#define IMU_H

#include <Arduino.h>
#include "MPU6050.h"
#include "Wire.h"

class Imu_handler {

  private :
    MPU6050 mpu;
  
    int16_t ax, ay, az;
    float accel_x = 0.0;
    float accel_y = 0.0;
    float accel_z = 0.0;

  public : 
    void update();


};

#endif