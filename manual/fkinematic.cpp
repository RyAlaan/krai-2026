#include "fkinematic.h"
#include "math.h"

float Fkinematic::Vx( float Vw1, float Vw2, float Vw3, float Vw4, float Venc1, 
                                        float angle1, float angle2, float angle3, float angle4, 
                                        float radius, float alpha) {
  float motorVx = (radius / 4) * (-sin(angle1) * Vw1 - sin(angle2) * Vw2 - sin(angle3) * Vw3 - sin(angle4) * Vw4);
  float encVx = Venc1;

  return alpha * motorVx + (1 - alpha) * encVx;
}

float Fkinematic::Vy( float Vw1, float Vw2, float Vw3, float Vw4, float Venc2, 
                                        float angle1, float angle2, float angle3, float angle4, 
                                        float radius, float alpha) {
  float motorVy = (radius / 4) * (cos(angle1) * Vw1 + cos(angle2) * Vw2 + cos(angle3) * Vw3 + cos(angle4) * Vw4);
  float encVy = Venc2;

  return alpha * motorVy + (1 - alpha) * encVy;
}

float Fkinematic::Omega(float Vw1, float Vw2, float Vw3, float Vw4, float radius, float distance) {
  return (radius / (4 * distance)) * (Vw1 + Vw2 + Vw3 + Vw4);
}
