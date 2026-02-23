#include "encoder.h"

Encoder *encoderPtr;

void updatePulse() {
  encoderPtr->updatePulse();
}

Encoder::Encoder(uint8_t pinClk, uint8_t pinDT, int PPR, int wheelRad) {
  this->pinClk = pinClk;
  this->pinDT = pinDT;
  this->PPR = PPR;
  this->wheelRad = wheelRad;
  this->pulseCounter = 0;
  this->prevPulse = 0;
  this->sampleTime = 0.1;

  pinMode(pinClk, INPUT_PULLUP);
  pinMode(pinDT, INPUT_PULLUP);

  encoderPtr = this;
  attachInterrupt(digitalPinToInterrupt(pinClk), updatePulse, RISING);  // akan memanggil method counter setiap kali pinClk mengalami clock RISING
}

// dilankan setiap kali valClk RISING
void Encoder::updatePulse() {
  bool valDT = digitalRead(pinDT);

  valDT ? pulseCounter++ : pulseCounter--;
}

float Encoder::getVelocity() {
  int deltaPulse = this->pulseCounter - this->prevPulse;

  // reset pulse
  this->prevPulse = this->pulseCounter;
  this->pulseCounter = 0;

  // count rpm
  float rpm = ((float)deltaPulse / (float)PPR) * (60.0f / sampleTime);

  // count velocity
  float velocity = (2 * PI * rpm) / 60;

  return velocity;
}
