#include "ikinematic.h"
#include "motor.h"

float Ikinematic::invKinematic(float angMotor, float vx, float vy, float omega) {
      return (-sin(angMotor) * vx) + (cos(angMotor) * vy) + (0.25 * omega);
}