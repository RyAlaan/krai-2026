#ifndef ODOMETRY_H
#define ODOMETRY_H

class Odometry {
  public :
    float x, y, theta;

    Odometry() : x(0), y(0), theta(0) {}

    void updateOdometry(float vx, float vy, float vtheta, float dt) {
      this->x = vx * dt;
      this->y = vy * dt;
      this->theta = vtheta * dt;
    }
};

#endif