#ifndef IMU_H
#define IMU_H

#include <Arduino.h>
#include "I2Cdev.h"
#include "MPU6050.h"
#include "Wire.h"

class IMU_Handler {

  private :
    MPU6050 mpu;
  
    int16_t ax, ay, az;

  public : 
    update_imu();

};

#endif