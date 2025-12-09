#ifndef FORKINEMATIC_H
#define FORKINEMATIC_H

#include <math.h>

class ForKinematic {
  private :
    float alpha, v_vw1, v_vw2, v_vw3, v_vw4;
    float alpha1, alpha2, alpha3, alpha4;
    const int PWM = 255;
    const float omega_max = 62.83; // 2 × π × putaran = 2 × π × 10 
    const float rad = 0.03;

  public :
    ForKinematic();

    // encoder velocity
    float encVelocityX(float alpha1, float alpha2, float v_vw1, float v_vw2) {
      float x1 = -sin(alpha) * v_vw1;
      float x2 = -sin(alpha) * v_vw2;
      return (x1 + x2);
    }

    float encVelocityY(float alpha1, float alpha2, float v_vw1, float v_vw2) {
      float y1 = cos(alpha) * v_vw1;
      float y2 = cos(alpha) * v_vw2;
      return (y1 + y2);
    }

    float omegaVelocity(float v_vw1, float v_vw2) {
      return v_vw1 + v_vw2; 
    }

    // motor velocity
    float velocityX(float alpha1, float alpha2, float alpha3, float alpha4, float v_vw1, float v_vw2, float v_vw3, float v_vw4) {
      float x1 = -sin(alpha1) * v_vw1;
      float x2 = -sin(alpha2) * v_vw2;
      float x3 = -sin(alpha3) * v_vw3;
      float x4 = -sin(alpha4) * v_vw4;
      return (this->rad / 4) * (x1 + x2 + x3 + x4);
    }

    float velocityY(float alpha1, float alpha2, float alpha3, float alpha4, float v_vw1, float v_vw2, float v_vw3, float v_vw4) {
      float y1 = cos(alpha1) * v_vw1;
      float y2 = cos(alpha2) * v_vw2;
      float y3 = cos(alpha3) * v_vw3;
      float y4 = cos(alpha4) * v_vw4;
      return (this->rad / 4) * (y1 + y2 + y3 + y4);
    }

    float omega(int v_vw1, int v_vw2, int v_vw3, int v_vw4) {
      return v_vw1 + v_vw2 + v_vw3 + v_vw4;
    }
};

#endif