#include "odometry.h"

void Odometry::update(float Vx, float Vy, float Omega, float deltaT) {
  this->x += Vx * deltaT;
  this->y += Vy * deltaT;
  this->theta += Omega * deltaT;
}