#include "Motor.h"

void Motor::beginPWM(uint32_t freq, uint8_t res)
{
  analogWriteResolution(res);
  analogWriteFrequency(freq);
}

Motor::Motor(uint8_t pin_sel, uint8_t pin_pwm)
: _sel(pin_sel), _pwm(pin_pwm)
{
  pinMode(_sel, OUTPUT);
  pinMode(_pwm, OUTPUT);
  analogWrite(_pwm, 0);
}

void Motor::CW(uint16_t value)
{
  digitalWrite(_sel, LOW);
  analogWrite(_pwm, value);
}

void Motor::CCW(uint16_t value)
{
  digitalWrite(_sel, HIGH);
  analogWrite(_pwm, value);
}

void Motor::STOP()
{
  analogWrite(_pwm, 0);
}