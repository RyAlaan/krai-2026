#ifndef MOTOR_H
#define MOTOR_H

#include <Arduino.h>

class Motor {
  public:
    /*   panggil sekali di setup()
         freq  = frekuensi PWM (Hz)
         res   = bit-resolusi PWM (1-16)  */
    static void beginPWM(uint32_t freq = 20000, uint8_t res = 12);

    Motor(uint8_t pin_selector, uint8_t pin_pwm);

    void cw (uint16_t duty);   // duty 0-(2^res-1)
    void ccw(uint16_t duty);
    void stop();

  private:
    uint8_t _sel, _pwm;
};

#endif
