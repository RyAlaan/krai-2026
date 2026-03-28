#ifndef KINEMATICS_H
#define KINEMATICS_H

#include <Arduino.h>
#include <FastTrig.h>

class Kinematics{
  private:
    float a1, a2, a3, a4;
    float ideal_a1; float ideal_a2; float ideal_a3; float ideal_a4;
    float sin_value[4] = {0,0,0,0}; float cos_value[4] = {0,0,0,0}; float err_cos_value[4] = {0,0,0,0};
  public:
    Kinematics();
    Kinematics(float a1, float a2, float a3, float a4);
    float Vw[4];
    void invers_kin(float Vx, float Vy, float Wr);
    void init(void);
    void set_ideal_value(float i_a1 = 45.49, float i_a2 = 134.51, float i_a3 = 225.49, float i_a4 = 314.51);
};

#endif