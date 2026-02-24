#include "Variable.h"

Motor roda1(sel_fr, pwm_fr);
Motor roda2(sel_fl, pwm_fl);
Motor roda3(sel_bl, pwm_bl);
Motor roda4(sel_br, pwm_br);


float manual_linear_rpm  = 150.0;   // translasi
float manual_angular_rpm = 100.0;   // rotasi

void setup() {
  Serial.begin(115200);
  Motor::beginPWM(20000, 12);

  rangkabawah = LowerPart(sel_fr, pwm_fr,
                          sel_fl, pwm_fl,
                          sel_bl, pwm_bl,
                          sel_br, pwm_br);

  calc = Kinematics(a1, a2, a3, a4, r, R);
  calc.set_ideal_value(a1_ideal, a2_ideal, a3_ideal, a4_ideal);
  calc.PPR = PPR;
  calc.init();
  calc.update_angle(0);

  motor1.SetMode(QuickPID::Control::automatic);
  motor2.SetMode(QuickPID::Control::automatic);
  motor3.SetMode(QuickPID::Control::automatic);
  motor4.SetMode(QuickPID::Control::automatic);

  motor1.SetOutputLimits(-4095, 4095);
  motor2.SetOutputLimits(-4095, 4095);
  motor3.SetOutputLimits(-4095, 4095);
  motor4.SetOutputLimits(-4095, 4095);
}

void loop() {

  /* ===================== KEYBOARD CONTROL ===================== */
  if (Serial.available()) {
    char key = Serial.read();

    if (key == 'w') {
      Vx = manual_linear_rpm;
      Vy = 0;
      Wr = 0;
    }
    else if (key == 's') {
      Vx = -manual_linear_rpm;
      Vy = 0;
      Wr = 0;
    }
    else if (key == 'a') {
      Vx = 0;
      Vy = manual_linear_rpm;
      Wr = 0;
    }
    else if (key == 'd') {
      Vx = 0;
      Vy = -manual_linear_rpm;
      Wr = 0;
    }
    else if (key == 'q') {
      Vx = 0;
      Vy = 0;
      Wr = manual_angular_rpm;
    }
    else if (key == 'e') {
      Vx = 0;
      Vy = 0;
      Wr = -manual_angular_rpm;
    }
    else if (key == 'x') {  
      Vx = 0;
      Vy = 0;
      Wr = 0;
    }
  }

  /* ===================== INVERSE KINEMATICS ===================== */
  calc.inverse_kinematics(Vx, Vy, Wr);
  
  /* ===================== BACA ENCODER ===================== */
  static long prev_fr = 0, prev_fl = 0, prev_bl = 0, prev_br = 0;
  static unsigned long prevTime = 0;

  long fr = ENCFR.read();
  long fl = ENCFL.read();
  long bl = ENCBL.read();
  long br = ENCBR.read();

  unsigned long now = micros();
  float dt = (now - prevTime) / 1e6;

  if (dt > 0.001) {

    Vreal1 = ((fr - prev_fr) / dt) / PPR * 60.0;
    Vreal2 = ((fl - prev_fl) / dt) / PPR * 60.0;
    Vreal3 = ((bl - prev_bl) / dt) / PPR * 60.0;
    Vreal4 = ((br - prev_br) / dt) / PPR * 60.0;

    Vfilt1 = Roda_1.updateEstimate(Vreal1);
    Vfilt2 = Roda_2.updateEstimate(Vreal2);
    Vfilt3 = Roda_3.updateEstimate(Vreal3);
    Vfilt4 = Roda_4.updateEstimate(Vreal4);

    prev_fr = fr;
    prev_fl = fl;
    prev_bl = bl;
    prev_br = br;
    prevTime = now;

    /* ===================== PID ===================== */
    Setpoint1 = calc.Vwheel[0];
    Setpoint2 = calc.Vwheel[1];
    Setpoint3 = calc.Vwheel[2];
    Setpoint4 = calc.Vwheel[3];

    motor1.Compute();
    motor2.Compute();
    motor3.Compute();
    motor4.Compute();

    rangkabawah.Movement(
      Output1,
      Output2,
      Output3,
      Output4
    );
  }

  /* ===================== DEBUG ===================== */
  Serial.print("Vx: "); Serial.print(Vx);
  Serial.print("  Vy: "); Serial.print(Vy);
  Serial.print("  Wr: "); Serial.print(Wr);
  Serial.print("  | RPM1: "); Serial.print(Vreal1);
  Serial.print("  RPM2: "); Serial.print(Vreal2);
  Serial.print("  RPM3: "); Serial.print(Vreal3);
  Serial.print("  RPM4: "); Serial.println(Vreal4);

}