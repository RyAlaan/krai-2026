#include "encoder.h"

Encoder *encoderPtr;

void counter() {
  encoderPtr->updatePulse();
}

Encoder::Encoder(uint8_t pinClk, uint8_t pinDT, int PPR) {
  this->pinClk = pinClk;
  this->pinDT = pinDT;
  this->PPR = PPR;
  this->pulseCounter = 0;
  this->prevPulse = 0;
  this->sampleTime = 0.1;

  pinMode(pinClk, INPUT_PULLUP);
  pinMode(pinDT, INPUT_PULLUP);

  encoderPtr = this;
  attachInterrupt(digitalPinToInterrupt(pinClk), counter, RISING); // akan memanggil method counter setiap kali pinClk mengalami clock RISING 
}


// dilankan setiap kali valClk RISING
void Encoder::updatePulse() {
  bool valDT= digitalRead(pinDT);

  valDT ? pulseCounter++ : pulseCounter--;
}

float Encoder::getRPM() {
  long currentPulse = this->pulseCounter; 

  long deltaPulse = currentPulse - this->prevPulse;
  this->prevPulse = currentPulse; 

  
  float revolutions = (float)deltaPulse / (float)PPR;

  // hitung RPM
  float rpm = revolutions * (60.0f / sampleTime);

  return rpm;
}


