#ifndef KINEMATIC_H
#define KINEMATIC_H

#include <math.h>

class Kinematic {
  private:
    float alpha, vx, vy, omega;

  public: 
    Kinematic();

    float invKinematic(float alpha, float vx, float vy, float vw) {
      return (-sin(alpha) * vx) + (cos(alpha) * vy) + (0.25 * vw);
    }
};

#endif