#include <cmath>
#include "Variable.h"

/* Untuk manual */
void MoveRobot(){
  /* Skala input direksional dari keyboard dengan target speed */
  /* target_linear_speed (misal 1800) akan menjadi nilai duty PWM Anda */
  Vx = rxStruct.Vx * target_linear_speed;
  Vy = rxStruct.Vy * target_linear_speed;
  Wr = rxStruct.W * target_angular_speed;

  // Hitung Inverse Kinematics untuk mendapat kecepatan target tiap roda
  calc.inverse_kinematics(Vx, Vy, Wr);

  // Kirim output IK langsung ke motor (Open-loop)
  // Constrain berfungsi agar nilai PWM aman di rentang resolusi STM32 (12-bit / -4095 hingga 4095)
  rangkabawah.Movement(
    constrain(calc.Vwheel[0], -4095, 4095),
    constrain(calc.Vwheel[1], -4095, 4095),
    constrain(calc.Vwheel[2], -4095, 4095),
    constrain(calc.Vwheel[3], -4095, 4095)
  );

  // Biarkan forward kinematics jika ingin mencetak nilai X, Y, Tetha untuk debugging
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