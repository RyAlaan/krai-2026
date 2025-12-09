#include "motor.h"

void Motor::PWM(int freq, int res) {
  analogWriteFrequency(freq);
  analogWriteResolution(res);
}

Motor::Motor(int PWM_PIN, int SEL_PIN) {
  this->PWM_PIN = PWM_PIN;
  this->SEL_PIN = SEL_PIN;

  pinMode(PWM_PIN, OUTPUT);
  pinMode(SEL_PIN, OUTPUT);

  analogWrite(this->PWM_PIN, 0);
}

void Motor::CW(int PWM_VAL) {
  digitalWrite(this->SEL_PIN, HIGH);
  analogWrite(this->PWM_PIN, PWM_VAL);
}

void Motor::CCW(int PWM_VAL) {
  digitalWrite(this->SEL_PIN, LOW);
  analogWrite(this->PWM_PIN, PWM_VAL);
}

void Motor::STOP() {
  analogWrite(this->PWM_PIN, 0);
}