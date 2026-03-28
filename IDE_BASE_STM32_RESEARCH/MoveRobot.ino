#include <cmath>
#include "Variable.h"

/* Untuk manual */
void MoveRobot(){
  /*------------------------Sistem Rangka Bawah------------------------------*/
  Vx = rxStruct.Vx * target_linear_speed;
  Vy = rxStruct.Vy * target_linear_speed;
  Wr = rxStruct.W * target_angular_speed;
  calc.inverse_kinematics(Vx, Vy, Wr);

  if(rxStruct.cmd == 'i'){
    target_linear_speed = 5000;
    target_angular_speed = 3000;
    Kp1 = 0.7, Ki1 = 20, Kd1 = 0;
    Kp2 = 0.7, Ki2 = 20, Kd2 = 0;
    Kp3 = 0.7, Ki3 = 20, Kd3 = 0;
    Kp4 = 0.7, Ki4 = 20, Kd4 = 0;

  }else{
    target_linear_speed = 1800;
    target_angular_speed = 900; 
    Kp1 = 0.5, Ki1 = 20, Kd1 = 0;
    Kp2 = 0.5, Ki2 = 20, Kd2 = 0;
    Kp3 = 0.5, Ki3 = 20, Kd3 = 0;
    Kp4 = 0.5, Ki4 = 20, Kd4 = 0;
  }

  // rodaFr.SetTunings(Kp1, Ki1, Kd1);
  // rodaFl.SetTunings(Kp2, Ki2, Kd2);
  // rodaBl.SetTunings(Kp3, Ki3, Kd3);
  // rodaBr.SetTunings(Kp4, Ki4, Kd4);

  if(prevL2 != rxStruct.cmd){
    if(rxStruct.cmd == 'j'){
      mirror = !mirror;
    }
    prevL2 = rxStruct.cmd;
  }

  if (PID_on) {
    if (mirror) {
      Setpoint1 = calc.Vwheel[2];
      Setpoint2 = calc.Vwheel[3];
      Setpoint3 = calc.Vwheel[0];
      Setpoint4 = calc.Vwheel[1];
    } else {
      Setpoint1 = calc.Vwheel[0];
      Setpoint2 = calc.Vwheel[1];
      Setpoint3 = calc.Vwheel[2];
      Setpoint4 = calc.Vwheel[3];
    }
  } else {
    // Open-loop movement for quick testing (no PID)
    if (mirror) {
      rangkabawah.Movement(constrain(calc.Vwheel[2], -4095, 4095), constrain(calc.Vwheel[3], -4095, 4095), constrain(calc.Vwheel[0], -4095, 4095), constrain(calc.Vwheel[1], -4095, 4095));
    } else {
      rangkabawah.Movement(constrain(calc.Vwheel[0], -4095, 4095), constrain(calc.Vwheel[1], -4095, 4095), constrain(calc.Vwheel[2], -4095, 4095), constrain(calc.Vwheel[3], -4095, 4095));
    }
  }
  
  // if(mirror){ // state kedua yang maju
  //   rangkabawah.Movement(constrain(calc.Vwheel[2], -4095, 4095), constrain(calc.Vwheel[3], -4095, 4095), constrain(calc.Vwheel[0], -4095, 4095), constrain(calc.Vwheel[1], -4095, 4095));
  // }else{ // state pertama maju
  //   rangkabawah.Movement(constrain(calc.Vwheel[0], -4095, 4095), constrain(calc.Vwheel[1], -4095, 4095), constrain(calc.Vwheel[2], -4095, 4095), constrain(calc.Vwheel[3], -4095, 4095));
  //   // rangkabawah.Movement(Output1, Output2, Output3, Output4);
  // }

  if (roller)
  {
    rangkabawahtengah.RollerMovement(Vy);
  }else{
    rangkabawahtengah.RollerMovement(0);
  }

  if (!PID_on){
    pwm1 += Output1; pwm2 += Output2; pwm3 += Output3; pwm4 += Output4;
    rangkabawah.Movement(constrain(pwm1, -4095, 4095), constrain(pwm2, -4095, 4095), constrain(pwm3, -4095, 4095), constrain(pwm4, -4095, 4095));
  } else {
    pwm1 = 0; pwm2 = 0; pwm3 = 0; pwm4 = 0;
    PID_reset();
    rangkabawah.Movement(constrain(calc.Vwheel[0], -4095, 4095), constrain(calc.Vwheel[1], -4095, 4095), constrain(calc.Vwheel[2], -4095, 4095), constrain(calc.Vwheel[3], -4095, 4095));
  }
  calc.forward_kinematics(Vfilt1, Vfilt2, Vfilt3, Vfilt4, false);
  calc.forward_kinematics(ENCFR.read(), ENCFL.read(), ENCBL.read(), ENCBR.read(), true);
}

/* Untuk Otonom */
// void MoveRobot() {
//   // float Vx = rxStruct.Vx; // Konversi cm/s ke m/s
//   // float Vy = rxStruct.Vy; // Konversi cm/s ke m/s
//   // float W = rxStruct.W; // rad/s
//   calc.inverse_kinematics(Vx, Vy, W);
//   float wheel_radius = r / 100.0; // Konversi cm ke m
//   Setpoint1 = calc.Vwheel[0] / (2 * PI * wheel_radius) * 60;
//   Setpoint2 = calc.Vwheel[1] / (2 * PI * wheel_radius) * 60;
//   Setpoint3 = calc.Vwheel[2] / (2 * PI * wheel_radius) * 60;
//   Setpoint4 = calc.Vwheel[3] / (2 * PI * wheel_radius) * 60;
//   Serial.println(calc.Vwheel[0]);
//   calc.inverse_kinematics(Vx, Vy, W);
//   rangkabawah.Movement(constrain(calc.Vwheel[0], -4095, 4095), constrain(calc.Vwheel[1], -4095, 4095), constrain(calc.Vwheel[2], -4095, 4095), constrain(calc.Vwheel[3], -4095, 4095));
//   Serial.println(txStruct.Vx);
//   Serial.println(Setpoint1);
//   Serial.print("Vwheel[0]: "); Serial.print(calc.Vwheel[0]); Serial.print(" m/s, Setpoint1: "); Serial.print(Setpoint1); Serial.println(" RPM");
//   Serial.print("Vwheel[1]: "); Serial.print(calc.Vwheel[1]); Serial.print(" m/s, Setpoint2: "); Serial.print(Setpoint2); Serial.println(" RPM");
//   Serial.print("Vwheel[2]: "); Serial.print(calc.Vwheel[2]); Serial.print(" m/s, Setpoint3: "); Serial.print(Setpoint3); Serial.println(" RPM");
//   Serial.print("Vwheel[3]: "); Serial.print(calc.Vwheel[3]); Serial.print(" m/s, Setpoint4: "); Serial.print(Setpoint4); Serial.println(" RPM");
//   calc.forward_kinematics(Vfilt1, Vfilt2, Vfilt3, Vfilt4, false);
//   calc.forward_kinematics(ENCFR.read(), ENCFL.read(), ENCBL.read(), ENCBR.read(), true);
// }