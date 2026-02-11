#include <math.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

#include "motor.h"
#include "kinematic.h"
#include "forKinematic.h"
#include "rangkaBawah.h"
#include "encoder.h"

//-----------------------Setup Object-----------------------/
Adafruit_MPU6050 mpu;
Kinematic kinematic;
ForKinematic forKinematic;
RangkaBawah rb;

//-----------------------Motor Pins Fix-----------------------/
//kanan depan (1) udah
#define sel_fr PA2
#define pwm_fr PB8
#define encA_fr PA6
#define encB_fr PB12

//kiri depan (2) udah
#define sel_fl PA3
#define pwm_fl PB7
#define encA_fl PA7
#define encB_fl PB13

//kiri belakang (3) udah
#define sel_bl PA4
#define pwm_bl PB6
#define encA_bl PA8
#define encB_bl PB14

//kanan belakang (4) udah
#define sel_br PA5
#define pwm_br PB9
#define encA_br PA9
#define encB_br PB15

//-----------------------Encoder External Pins-----------------------/
#define encA_X 18
#define encB_X 19

#define encA_Y 20
#define encB_Y 21

#define pprMotor 134.0
#define pprEnc 600.0

// radius Motor & Encoder
float radiusMotor =  0.05;
float radEnc =  0.0275;

//-----------------------Setup Motor-----------------------/
Motor motor1(pwm_fr, sel_fr);
Motor motor2(pwm_fl, sel_fl);
Motor motor3(pwm_bl, sel_bl);
Motor motor4(pwm_br, sel_br);

float angMotor1 = 45.21 * (PI/180);
float angMotor2 = 135.21 * (PI/180);
float angMotor3 = 225.21 * (PI/180);
float angMotor4 = 315.21 * (PI/180);

Encoder encoder1(encA_fr, encB_fr, pprMotor, radMotor);
Encoder encoder2(encA_fl, encB_fl, pprMotor, radMotor);
Encoder encoder3(encA_bl, encB_bl, pprMotor, radMotor);
Encoder encoder4(encA_br, encB_br, pprMotor, radMotor);

//-----------------------Setup Encoder-----------------------/
double angEncX = 0 ;
double angEncY = 90 * (3.14/180);

Encoder encoderX(encA_X, encB_X, pprEnc, radEnc);
Encoder encoderY(encA_Y, encB_Y, pprEnc, radEnc);

// Motor & encoder radius
float distanceMotor = 32.8873;
float distanceY = 34.75;
float distanceX = 34.5;

// velocity
float v_vw1 = 0, v_vw2 = 0, v_vw3 = 0, v_vw4 = 0, encVx = 0, encVy = 0;
float Vx = 0, Vy = 0, Omega = 0;

int PWM = 4085;

float alpha, vx, vy;

typedef struct {
  int LX, LY, RX, RY;
  bool arrUP, arrDOWN, arrLEFT, arrRIGHT;
} PS2Packet;

PS2Packet action;

float lx, ly, ry;
char key;

unsigned long currTime = 0;
float dt = 0;

int normalize(long value) {
  return map(value, 0, 225, -127, 127);
}

void setup() {
  Serial.begin(115200);
  Serial1.begin(9600);

  Motor::PWM(20000, 12);

  rb = RangkaBawah(
    pwm_fr, sel_fr,
    pwm_fl, sel_fl,
    pwm_bl, sel_bl,
    pwm_br, sel_br
  );

  //-----------------------Initialize MPU6050-----------------------/
  // if (!mpu.begin()) {
  //   Serial.println("Failed to find MPU6050 chip");
  //   while (1) {
  //     delay(10);
  //   }
  // }
  // Serial.println("MPU6050 Found!");

  // mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  // mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  // mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
}

void loop() {

  currTime = micros();
  dt = (currTime - prevTime) / 1e6;
  prevTime = currTime;

  //-----------------------Input Controller-----------------------/
  lx = normalize(action.LX);
  ly = normalize(action.LY);
  ry = normalize(action.RY);

  alpha = atan2(lx, ly);
  if(fabs(lx) < 60 && fabs(ly) < 60) {
    vx = 0;
    vy = 0;
  } else {
    vx = PWM * cos(alpha);  
    vy = PWM * sin(alpha) * -1;
  }

  //-----------------------Input Serial-----------------------/
  if (Serial.available() > 0) {
      key = Serial.read();
  }

  switch (key) {
    case 'W': case 'w': vy =  PWM; break;
    case 'S': case 's': vy = -PWM; break;
    case 'A': case 'a': vx = -PWM; break;
    case 'D': case 'd': vx =  PWM; break;

    case 'Q': case 'q': ry =  300; break;
    case 'E': case 'e': ry = -300; break;

    case 'X': case 'x': vx = 0; vy = 0; ry = 0; break;
  }

  //-----------------------get IMU values-----------------------/
  // sensors_event_t a, g;
  // mpu.getEvent(&a, &g);

  //-----------------------inverse kinematic-----------------------/
  v_vw1 = kinematic.invKinematic(angMotor1, vx, vy, ry);
  v_vw2 = kinematic.invKinematic(angMotor2, vx, vy, ry);
  v_vw3 = kinematic.invKinematic(angMotor3, vx, vy, ry);
  v_vw4 = kinematic.invKinematic(angMotor4, vx, vy, ry);

  //-----------------------get velocity from external encoder-----------------------/
  velocityX = forKinematic.encVelocityX(angEncX, angEncY, encoderX.getVelocity(), encoderY.getVelocity());
  velocityY = forKinematic.encVelocityY(angEncX, angEncY, encoderX.getVelocity(), encoderY.getVelocity());
  omegaVel = forKinematic.omegaVelocity(encoderX.getVelocity(), encoderY.getVelocity());

  // Serial.print("VelX: "); Serial.print(velocityX);
  // Serial.print(" | VelY: "); Serial.print(velocityY);
  // Serial.print(" | Omega: "); Serial.println(omegaVel);

  //-----------------------wheel drive-----------------------/
  rb.moveRobot(v_vw1, v_vw2, v_vw3, v_vw4);
}
