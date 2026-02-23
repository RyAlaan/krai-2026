#include "Variable.h"

Motor roda1(sel_fr, pwm_fr); // roda 4
Motor roda2(sel_fl, pwm_fl); // roda 2
Motor roda3(sel_bl, pwm_bl); // roda 1
Motor roda4(sel_br, pwm_br); // roda 3

void setup() {
  Serial.begin(115200);
  Motor::beginPWM(20000, 12);

  pinMode(LED, OUTPUT); 
  digitalWrite(LED, LOW);
  pinMode(rpwm_mid, OUTPUT);
  pinMode(lpwm_mid, OUTPUT);

  //OBJECT CONSTRUCTING
  rangkabawah = LowerPart(sel_fr, pwm_fr, sel_fl, pwm_fl, sel_bl, pwm_bl, sel_br, pwm_br);
  rangkabawahtengah = LowerPartMid(rpwm_mid, lpwm_mid);
  calc = Kinematics(a1, a2, a3, a4, r, R);
  calc.set_ideal_value(a1_ideal, a2_ideal, a3_ideal, a4_ideal);
  calc.PPR = PPR  ;
  calc.init();
  calc.update_angle(0);
  myTransfer.begin(Serial);
}

void loop() {

  receive();

  

}