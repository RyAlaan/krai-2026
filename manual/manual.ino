#include <math.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

#include "header.h"
#include "motor.h"
#include "rangkaBawah.h"
#include "encoder.h"
#include "fkinematic.h"
#include "odometry.h"

// ------------------ Objects Setup ------------------
Odometry odom;
Fkinematic fkinematic;

// ------------------ Motor Setup ------------------
Motor motor1(pwm_fr, sel_fr);
Motor motor2(pwm_fl, sel_fl);
Motor motor3(pwm_bl, sel_bl);
Motor motor4(pwm_br, sel_br);

// ------------------ Radius Motor & Encoder ------------------
float radiusMotor = 0.05;
float radiusEnc = 0.0275;

// ------------------ Encoder Setup ------------------
Encoder encMotor1(enc1A, enc1B, pprMotor, radiusMotor);
Encoder encMotor2(enc2A, enc2B, pprMotor, radiusMotor);
Encoder encMotor3(enc3A, enc3B, pprMotor, radiusMotor);
Encoder encMotor4(enc4A, enc4B, pprMotor, radiusMotor);

Encoder encX(encxA, encxB, pprEnc, radiusEnc);
Encoder encY(encyA, encyB, pprEnc, radiusEnc);

// ------------------ Define Alpha ------------------
float angMotor1 = 45.21 * (PI/180);
float angMotor2 = 135.21 * (PI/180);
float angMotor3 = 225.21 * (PI/180);
float angMotor4 = 315.21 * (PI/180);

float angEncX = 270 * (PI/180);
float angEncY = 180 * (PI/180);

float distanceMotor = 32.8873;

unsigned long prevTime = 0;

float v1 = 1, v2 = 0, v3 = 0, v4 = 0, vxEnc = 0, vyEnc = 0;
float vx = 0, vy = 0, w = 0;

// ------------------ ISR Wrap ------------------
void ISR_m1() { encMotor1.updatePulse(); }
void ISR_m2() { encMotor2.updatePulse(); }
void ISR_m3() { encMotor3.updatePulse(); }
void ISR_m4() { encMotor4.updatePulse(); }

void ISR_encX() { encX.updatePulse(); }
void ISR_encY() { encY.updatePulse(); }

void setup () {
  Serial.begin(115200);

  Motor::PWM(20000, 12);

  RangkaBawah rb(
    pwm_fr, sel_fr,
    pwm_fl, sel_fl,
    pwm_bl, sel_bl,
    pwm_br, sel_br
  );

  encMotor1.begin();  encMotor2.begin();
  encMotor3.begin();  encMotor4.begin();

  encX.begin();  encY.begin();

  attachInterrupt(digitalPinToInterrupt(enc1A), ISR_m1, RISING);
  attachInterrupt(digitalPinToInterrupt(enc2A), ISR_m2, RISING);
  attachInterrupt(digitalPinToInterrupt(enc3A), ISR_m3, RISING);
  attachInterrupt(digitalPinToInterrupt(enc4A), ISR_m4, RISING);
  
  attachInterrupt(digitalPinToInterrupt(encxA), ISR_encX, RISING);
  attachInterrupt(digitalPinToInterrupt(encyA), ISR_encY, RISING);
}

void loop () {
  unsigned long now = micros();
  float dt = (now - prevTime) * 1e-6;
  prevTime = now;

  v1 = encMotor1.getVelocity(dt);
  v2 = encMotor2.getVelocity(dt);
  v3 = encMotor3.getVelocity(dt);
  v4 = encMotor4.getVelocity(dt);

  vxEnc = encX.getVelocity(dt);
  vyEnc = encY.getVelocity(dt);

  vx = fkinematic.Vx(v1, v2, v3, v4, vxEnc, angMotor1, angMotor2, angMotor3, angMotor4, radiusMotor,  0.5);
  vy = fkinematic.Vy(v1, v2, v3, v4, vyEnc, angMotor1, angMotor2, angMotor3, angMotor4, radiusMotor,  0.5);
  w = fkinematic.Omega(v1, v2, v3, v4, radiusMotor, distanceMotor);

  odom.update(vx, vy, w, dt);

  Serial.print("Vx: "); Serial.print(vx);
  Serial.print(" Vy: "); Serial.print(vy);
  Serial.print(" W: ");  Serial.println(w);
}

