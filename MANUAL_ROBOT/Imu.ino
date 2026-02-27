/*----------------------------------------------
  ---------PROPERTY OF BLAKASUTHA_UNSOED--------
  ----------------------------------------------
  IMU.ino - Implementasi IMU_Handler
  MPU6050 Yaw Calculation untuk Field-Oriented Control
----------------------------------------------*/

#include "IMU.h"

// ---- KONSTRUKTOR ----
IMU_Handler::IMU_Handler() {}

// ---- BEGIN ----
bool IMU_Handler::begin() {
  Wire.begin();
  Wire.setClock(400000); // Fast mode I2C 400kHz

  mpu.initialize();

  if (!mpu.testConnection()) {
    return false; // MPU6050 tidak terdeteksi
  }

  // Set range gyroscope ke ±250 deg/s (paling sensitif)
  mpu.setFullScaleGyroRange(MPU6050_GYRO_FS_250);

  // Set range accelerometer ke ±2g
  mpu.setFullScaleAccelRange(MPU6050_ACCEL_FS_2);

  // Kalibrasi offset gyro
  calibrate(500);

  prev_time = millis();
  is_ready  = true;
  return true;
}

// ---- KALIBRASI ----
// Robot harus DIAM saat kalibrasi (dipanggil di setup())
void IMU_Handler::calibrate(int samples) {
  float sum = 0.0;
  for (int i = 0; i < samples; i++) {
    mpu.getRotation(&gx, &gy, &gz);
    sum += (float)gz / GYRO_SCALE_FACTOR;
    delay(2);
  }
  gyro_z_offset = sum / samples;
}

// ---- KALMAN FILTER ----
float IMU_Handler::kalman_update(float measurement) {
  // Predict
  kf_p = kf_p + kf_q;
  // Update
  float K  = kf_p / (kf_p + kf_r); // Kalman Gain
  kf_x     = kf_x + K * (measurement - kf_x);
  kf_p     = (1 - K) * kf_p;
  return kf_x;
}

// ---- UPDATE (panggil tiap inputrate ms) ----
void IMU_Handler::update_imu() {
  if (!is_ready) return;

  unsigned long curr_time = millis();
  float dt = (curr_time - prev_time) / 1000.0; // detik
  prev_time = curr_time;

  // Baca raw gyro
  mpu.getRotation(&gx, &gy, &gz);

  // Konversi ke deg/s dan kurangi offset
  float gz_dps = ((float)gz / GYRO_SCALE_FACTOR) - gyro_z_offset;

  // Terapkan deadzone untuk meredam drift saat diam
  if (fabsf(gz_dps) < GYRO_DEADZONE) gz_dps = 0.0;

  // Kalman filter
  gyro_z = kalman_update(gz_dps);

  // Integrasi → yaw angle
  psi += gyro_z * dt;

  // Normalisasi psi ke range -180 ~ 180 derajat
  if      (psi >  180.0) psi -= 360.0;
  else if (psi < -180.0) psi += 360.0;
}

// ---- RESET YAW ----
void IMU_Handler::reset_yaw() {
  psi    = 0.0;
  kf_x   = 0.0;
  kf_p   = 1.0;
}
