#include "Imu.h"

void Imu_handler::update(){

  mpu.getAcceleration(&ax, &ay, &az);
  accel_x = (ax / 16384.0) * 9.81;
  accel_y = (ay / 16384.0) * 9.81;
  accel_z = (az / 16384.0) * 9.81;

}