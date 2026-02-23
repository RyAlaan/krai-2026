#include "Motor.h"

void Motor::beginPWM(uint32_t freq, uint8_t res)
{
  analogWriteResolution(res);
  analogWriteFrequency(freq);
}

Motor::Motor(uint8_t pin_pwm, uint8_t pin_selector): _pwm(pin_pwm), _sel(pin_selector)
{
  pinMode(_sel, OUTPUT);
  pinMode(_pwm, OUTPUT);
  analogWrite(_pwm, 0); 
}

Motor::CW(uint16_t value)
{
  digitalWrite(_sel, HIGH);
  analogWrite(_pwm, value);
}

Motor::CCW(uint16_t value)
{
  digitalWrite(_sel, HIGH);
  analogWrite(_pwm, value);
}

Motor::CCW(uint16_t value)
{
  analogWrite(_pwm, 0);
}