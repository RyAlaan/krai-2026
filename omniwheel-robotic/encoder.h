#ifndef ENCODER_H
#define ENCODER_H

// ------- Encoder
// ------- Documentation : https://docs.wokwi.com/parts/wokwi-ky-040

#include <Arduino.h>

class Encoder {
  private :
    uint8_t pinClk, pinDT; // pin encoder
    int PPR; // pulse per revolution 
    int wheelRad; // wheel radius in m
    int pulseCounter;
    int prevPulse;
    float sampleTime;
    float velocity;

  public :
    Encoder(uint8_t pinClk, uint8_t pinDT, int PPR, int wheelRad);
  
    void updatePulse();
    float getDistance(float combVelocity);
    float getVelocity();
};

#endif