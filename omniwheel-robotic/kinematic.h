#ifndef KINEMATIC_H
#define KINEMATIC_H

#include <math.h>

class Kinematic {
  public: 
    Kinematic();

    float invKinematic(float angMotor, float vx, float vy, float vw) {
      return (-sin(angMotor) * vx) + (cos(angMotor) * vy) + (0.25 * vw);
    }
};

#endif