#ifndef RANGKA_BAWAH_H
#define RANGKA_BAWAH_H

#include <cstdint>
#include "motor.h"

using namespace std;

class RangkaBawah {
  private:
    Motor motor1;
    Motor motor2;
    Motor motor3;
    Motor motor4;
    
  public :
    RangkaBawah();
    RangkaBawah(
      int pwm_fr, int sel_fr,
      int pwm_fl, int sel_fl,
      int pwm_bl, int sel_bl,
      int pwm_br, int sel_br
    );

    void moveRobot(float v_w1, float v_w2, float v_w3, float v_w4);
};

#endif