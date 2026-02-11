#ifndef FORKINEMATIC_H
#define FORKINEMATIC_H

#include <math.h>

class ForKinematic {
  // private :
  //   float alpha, v_vw1, v_vw2, v_vw3, v_vw4;
  //   float angMotor1, angMotor2, angMotor3, angMotor4;

  public :
    ForKinematic();

    // encoder velocity
    float encVelocityX(float angMotor1, float angMotor2, float v_vw1, float v_vw2, float radEnc) {
      float x1 = -sin(alpha) * v_vw1;
      float x2 = -sin(alpha) * v_vw2;
      return (x1 + x2); 
    }

    float encVelocityY(float angMotor1, float angMotor2, float v_vw1, float v_vw2) {
      float y1 = cos(alpha) * v_vw1;
      float y2 = cos(alpha) * v_vw2;
      return (y1 + y2);
    }

    float omegaVelocity(float v_vw1, float v_vw2) {
      return v_vw1 + v_vw2; 
    }

    // motor velocity
    float velocityX(float angMotor1, float angMotor2, float angMotor3, float angMotor4, float v_vw1, float v_vw2, float v_vw3, float v_vw4, float encVx, float radiusMotor,) {
      float motorVx = (radiusMotor / 4) * (-sin(angMotor1) * v_vw1 - sin(angMotor2) * v_vw2 - sin(angMotor3) * v_vw3 - sin(angMotor4) * v_vw4);
      return alpha * motorVx + (1 - alpha) *  ;
    }

    float velocityY(float angMotor1, float angMotor2, float angMotor3, float angMotor4, float v_vw1, float v_vw2, float v_vw3, float v_vw4, float encVy, float radiusMotor) {
      float motorVy = (radiusMotor / 4) * (-sin(angMotor1) * v_vw1 - sin(angMotor2) * v_vw2 - sin(angMotor3) * v_vw3 - sin(angMotor4) * v_vw4);
      return alpha * motorVy + (1 - alpha) * encVy;
    }

    float getOmega(float v_vw1, float v_vw2, float v_vw3, float v_vw4, float radiusMotor, float distanceMotor) {
      return (radiusMotor / (4 * distanceMotor)) * (v_vw1 + v_vw2 + v_vw3 + v_vw4);
    }
};

#endif