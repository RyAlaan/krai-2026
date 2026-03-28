#include "Motor.h"

/* ------------  fungsi statis  ---------------- */
void Motor::beginPWM(uint32_t freq, uint8_t res)
{
  analogWriteResolution(res);     // berlaku global
  analogWriteFrequency(freq);     // berlaku global
}

/* ------------  konstruktor objek  ------------ */
Motor::Motor(uint8_t pin_selector, uint8_t pin_pwm)
: _sel(pin_selector), _pwm(pin_pwm)
{
  pinMode(_sel, OUTPUT);
  pinMode(_pwm, OUTPUT);
  analogWrite(_pwm, 0);           // pastikan motor mati
}

/* ------------  aksi motor  ------------------- */
void Motor::cw(uint16_t duty)
{
  digitalWrite(_sel, HIGH);
  analogWrite(_pwm, duty);
}

void Motor::ccw(uint16_t duty)
{
  digitalWrite(_sel, LOW);
  analogWrite(_pwm, duty);
}

void Motor::stop()
{
  analogWrite(_pwm, 0);
}
