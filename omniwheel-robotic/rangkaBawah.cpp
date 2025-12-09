#include "rangkaBawah.h"
#include <cmath>

RangkaBawah::RangkaBawah(): motor1(0, 0), motor2(0, 0), motor3(0, 0), motor4(0,0) {};
RangkaBawah::RangkaBawah(
  int pwm1, int sel1,
  int pwm2, int sel2,
  int pwm3, int sel3,
  int pwm4, int sel4
): motor1(pwm1, sel1), 
   motor2(pwm2, sel2), 
   motor3(pwm3, sel3),
   motor4(pwm4, sel4)
{};

void RangkaBawah::moveRobot(float v_w1, float v_w2, float v_w3, float v_w4) {
  if (v_w1 > 0) {
    motor1.CW(static_cast<uint16_t>(fabs(v_w1)));
  } else if (v_w1 < 0) {
    motor1.CCW(static_cast<uint16_t>(fabs(v_w1)));
  } else {
    motor1.STOP();
  }

  if (v_w2 > 0) {
    motor2.CW(static_cast<uint16_t>(fabs(v_w2)));
  } else if (v_w2 < 0) {
    motor2.CCW(static_cast<uint16_t>(fabs(v_w2)));
  } else {  
    motor2.STOP();
  }

  if (v_w3 > 0) {
    motor3.CW(static_cast<uint16_t>(fabs(v_w3)));
  } else if (v_w3 < 0) {
    motor3.CCW(static_cast<uint16_t>(fabs(v_w3)));
  } else {
    motor3.STOP();
  }

  if (v_w4 > 0) {
    motor4.CW(static_cast<uint16_t>(fabs(v_w4)));
  } else if (v_w4 < 0) {
    motor4.CCW(static_cast<uint16_t>(fabs(v_w4)));
  } else {
    motor4.STOP();
  }
};