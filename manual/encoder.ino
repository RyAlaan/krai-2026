#include "encoder.h"
#include <math.h>

Encoder::Encoder(int pin_a, int pin_b, float PPR, float radius) {
  this->pin_a = pin_a;
  this->pin_b = pin_b;

  this->PPR = PPR;
  this->perimeter = 2 * PI * radius;
}

void Encoder::begin() {
  pinMode(pin_a, INPUT_PULLUP);
  pinMode(pin_b, INPUT_PULLUP);
}

void Encoder::updatePulse() {
  int stateB = digitalRead(this->pin_b);
  this->pulseCount += (stateB > 0) ? 1 : -1;
}


float Encoder::getVelocity(float deltaT) {
  int currPulse = this->pulseCount;
  int deltaPulse = this->pulseCount - this->prevPulse;
  this->prevPulse = currPulse;

  return (deltaPulse / deltaT) * (1 / this->PPR) * this->perimeter;
}