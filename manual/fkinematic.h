#ifndef FKINEMATIC_H
#define FKINEMATIC_H

class Fkinematic {
  public :
    float Vx(
      float Vw1, float Vw2, float Vw3, float Vw4, float Venc1,
      float angle1, float angle2, float angle3, float angle4,
      float radius, float alpha
    );

    float Vy(
      float Vw1, float Vw2, float Vw3, float Vw4, float Venc2,
      float angle1, float angle2, float angle3, float angle4,
      float radius, float alpha
    );

    float Omega(float Vw1, float Vw2, float Vw3, float Vw4, float radius, float distance);
};

#endif