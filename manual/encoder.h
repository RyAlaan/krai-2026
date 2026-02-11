#ifndef ENCODER_H
#define ENCODER_H

class Encoder {
  private : 
    int pin_a, pin_b; // pin_clk, pin_dt
    float PPR; 
    float perimeter;
    long prevPulse;
    volatile long pulseCount;

  public :
    Encoder(int pin_a, int pin_b, float PPR, float radius);

    void begin();
    void updatePulse();
    long getPulse();
    float getVelocity(float deltaT);
};

#endif 