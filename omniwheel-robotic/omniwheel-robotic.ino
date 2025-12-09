#include <math.h>

#include "motor.h"
#include "kinematic.h"
#include "forKinematic.h"
#include "rangkaBawah.h"
#include "encoder.h"

//-----------------------Setup Object-----------------------/
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

//-----------------------Setup Motor-----------------------/
Motor motor1(pwm_fr, sel_fr);
Motor motor2(pwm_fl, sel_fl);
Motor motor3(pwm_bl, sel_bl);
Motor motor4(pwm_br, sel_br);

double rad1 = 44.8 * (3.14/180);
double rad2 = 135.2 * (3.14/180);
double rad3 = 224.8 * (3.14/180);
double rad4 = 315.2 * (3.14/180);

//-----------------------Setup Encoder-----------------------/
Encoder encoderX(encA_X, encB_X, 134);
Encoder encoderY(encA_Y, encB_Y, 134);

double radEncX = 0 ;
double radEncY = 90 * (3.14/180);

int PWM = 4085;

float alpha, vx, vy;

typedef struct {
  int LX, LY, RX, RY;
  bool arrUP, arrDOWN, arrLEFT, arrRIGHT;
} PS2Packet;

PS2Packet action;

float lx, ly, ry;
char key;

float v_vw1, v_vw2, v_vw3, v_vw4;

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
}

void loop() {
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

  // --- membaca input keyboard dari Serial ---
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

  v_vw1 = kinematic.invKinematic(rad1, vx, vy, ry);
  v_vw2 = kinematic.invKinematic(rad2, vx, vy, ry);
  v_vw3 = kinematic.invKinematic(rad3, vx, vy, ry);
  v_vw4 = kinematic.invKinematic(rad4, vx, vy, ry);

  rb.moveRobot(v_vw1, v_vw2, v_vw3, v_vw4);
}
