#ifndef ENCODER_H
#define ENCODER_H

// ------- Encoder
// ------- Documentation : https://docs.wokwi.com/parts/wokwi-ky-040

#include <Arduino.h>

class Encoder {
  private :
    uint8_t pinClk, pinDT;
    int PPR;
    int pulseCounter;
    int prevPulse;
    float sampleTime;
    float RPMValue;

  public :
    Encoder(uint8_t pinClk, uint8_t pinDT, int PPR);

    void updatePulse();
    float getRPM();
};

#endif