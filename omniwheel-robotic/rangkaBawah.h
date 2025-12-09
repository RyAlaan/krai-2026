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
      int pwm1, int sel1,
      int pwm2, int sel2,
      int pwm3, int sel3,
      int pwm4, int sel4
    );

    void moveRobot(float v_w1, float v_w2, float v_w3, float v_w4);
};

#endif