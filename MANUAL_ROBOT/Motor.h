#ifndef MOTOR_H
#define MOTOR_H

#include <Arduino.h>

class Motor {
  
  private :
    uint8_t _pwm, _sel;

  public :
    static void beginPWM(uint32_t freq = 20000, uint8_t res = 12);

    Motor(uint8_t pwm, uint8_t sel);

    void CW(uint16_t value);
    void CCW(uint16_t value);
    void STOP();

};

#endif