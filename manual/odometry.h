#ifndef ODOMETRY_H
#define ODOMETRY_H

class Odometry {
  private :
    float x = 0.0;
    float y = 0.0;
    float theta = 0.0;

  public :
    void update(float Vx, float Vy, float Omega, float deltaT);
};

#endif