#include "rangkaBawah.h"
#include <cmath>

RangkaBawah::RangkaBawah(): motor1(0, 0), motor2(0, 0), motor3(0, 0), motor4(0,0) {};
RangkaBawah::RangkaBawah(
  int pwm_fr, int sel_fr,
  int pwm_fl, int sel_fl,
  int pwm_bl, int sel_bl,
  int pwm_br, int sel_br
): motor1(pwm_fr, sel_fr), 
   motor2(pwm_fl, sel_fl), 
   motor3(pwm_bl, sel_bl),
   motor4(pwm_br, sel_br)
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