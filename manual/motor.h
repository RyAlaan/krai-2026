#ifndef MOTOR_H
#define MOTOR_H

#include <math.h>

class Motor {
  private : 
    int PWM_PIN, SEL_PIN;

  public :
    static void PWM(int freq = 20000, int res = 12);
    Motor(int PWM_PIN, int SEL_PIN);

    void CW(int PWM_VAL);
    void CCW(int PWM_VAL);
    void STOP();
};

#endif