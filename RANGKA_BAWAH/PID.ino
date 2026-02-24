// void PID_init(){
//   motor1.SetOutputLimits(-4095, 4095);
//   motor2.SetOutputLimits(-4095, 4095);
//   motor3.SetOutputLimits(-4095, 4095);
//   motor4.SetOutputLimits(-4095, 4095);

//   motor1.SetSampleTimeUs(inputrate*1000);
//   motor2.SetSampleTimeUs(inputrate*1000);
//   motor3.SetSampleTimeUs(inputrate*1000);
//   motor4.SetSampleTimeUs(inputrate*1000);

//   motor1.SetTunings(Kp1, Ki1, Kd1);
//   motor2.SetTunings(Kp2, Ki2, Kd2);
//   motor3.SetTunings(Kp3, Ki3, Kd3);
//   motor4.SetTunings(Kp4, Ki4, Kd4);

//   motor1.SetMode(motor1.Control::automatic);
//   motor2.SetMode(motor2.Control::automatic);
//   motor3.SetMode(motor3.Control::automatic);
//   motor4.SetMode(motor4.Control::automatic);
// }

// // void PID_compute(){
// //   motor1.Compute();
// //   motor2.Compute();
// //   motor3.Compute();
// //   motor4.Compute();
// // }

// void PID_compute() {
//   // Input sudah dalam RPM dari Vfilt1 hingga Vfilt4
//   // Setpoint sudah dalam RPM dari MoveRobot()
//   motor1.Compute();
//   motor2.Compute();
//   motor3.Compute();
//   motor4.Compute();

//   // Terapkan output ke motor
//   rangkabawah.Movement(constrain(Output1, -4095, 4095),
//                        constrain(Output2, -4095, 4095),
//                        constrain(Output3, -4095, 4095),
//                        constrain(Output4, -4095, 4095));

//   // Cetak untuk debugging
//   if (!stop) {
//     static unsigned long lastPrint = 0;
//     if (millis() - lastPrint >= 100) { // Cetak setiap 100ms
//       Serial.print("PID1: Set="); Serial.print(calc.Vwheel[0]); Serial.print(" RPM, In="); Serial.print(Vfilt1); Serial.print(" RPM, Out="); Serial.println(Output1);
//       Serial.print("PID2: Set="); Serial.print(calc.Vwheel[1]); Serial.print(" RPM, In="); Serial.print(Vfilt2); Serial.print(" RPM, Out="); Serial.println(Output2);
//       Serial.print("PID3: Set="); Serial.print(calc.Vwheel[2]); Serial.print(" RPM, In="); Serial.print(Vfilt3); Serial.print(" RPM, Out="); Serial.println(Output3);
//       Serial.print("PID4: Set="); Serial.print(calc.Vwheel[3]); Serial.print(" RPM, In="); Serial.print(Vfilt4); Serial.print(" RPM, Out="); Serial.println(Output4);
//       lastPrint = millis();
//     }
//   }
// }

// void PID_reset(){
//   motor1.Reset();
//   motor2.Reset();
//   motor3.Reset();
//   motor4.Reset();
// }



// void PID_init() {
//   Kp1 = Kp2 = Kp3 = Kp4 = 5.0; // Nilai awal Kp
//   Ki1 = Ki2 = Ki3 = Ki4 = 0.0;
//   Kd1 = Kd2 = Kd3 = Kd4 = 0.0;
//   motor1.SetTunings(Kp1, Ki1, Kd1);
//   motor2.SetTunings(Kp2, Ki2, Kd2);
//   motor3.SetTunings(Kp3, Ki3, Kd3);
//   motor4.SetTunings(Kp4, Ki4, Kd4);
//   motor1.SetOutputLimits(-4095, 4095);
//   motor2.SetOutputLimits(-4095, 4095);
//   motor3.SetOutputLimits(-4095, 4095);
//   motor4.SetOutputLimits(-4095, 4095);
//   motor1.SetSampleTimeUs(inputrate * 1000);
//   motor2.SetSampleTimeUs(inputrate * 1000);
//   motor3.SetSampleTimeUs(inputrate * 1000);
//   motor4.SetSampleTimeUs(inputrate * 1000);
//   motor1.SetMode(motor1.Control::automatic);
//   motor2.SetMode(motor2.Control::automatic);
//   motor3.SetMode(motor3.Control::automatic);
//   motor4.SetMode(motor4.Control::automatic);
// }

// void PID_compute() {
//   motor1.Compute();
//   motor2.Compute();
//   motor3.Compute();
//   motor4.Compute();
//   rangkabawah.Movement(constrain(Output1, -4095, 4095),
//                        constrain(Output2, -4095, 4095),
//                        constrain(Output3, -4095, 4095),
//                        constrain(Output4, -4095, 4095));
//   if (!stop) {
//     static unsigned long lastPrint = 0;
//     if (millis() - lastPrint >= 100) {
//       Serial.print("PID1: Set="); Serial.print(Setpoint1); Serial.print(" RPM, In="); Serial.print(Vfilt1); Serial.print(" RPM, Out="); Serial.println(Output1);
//       Serial.print("PID2: Set="); Serial.print(Setpoint2); Serial.print(" RPM, In="); Serial.print(Vfilt2); Serial.print(" RPM, Out="); Serial.println(Output2);
//       Serial.print("PID3: Set="); Serial.print(Setpoint3); Serial.print(" RPM, In="); Serial.print(Vfilt3); Serial.print(" RPM, Out="); Serial.println(Output3);
//       Serial.print("PID4: Set="); Serial.print(Setpoint4); Serial.print(" RPM, In="); Serial.print(Vfilt4); Serial.print(" RPM, Out="); Serial.println(Output4);
//       lastPrint = millis();
//     }
//   }
// }

// void PID_reset() {
//   motor1.Reset();
//   motor2.Reset();
//   motor3.Reset();
//   motor4.Reset();
// }



void PID_init(){
  motor1.SetOutputLimits(-4095, 4095);
  motor2.SetOutputLimits(-4095, 4095);
  motor3.SetOutputLimits(-4095, 4095);
  motor4.SetOutputLimits(-4095, 4095);

  motor1.SetSampleTimeUs(inputrate*1000);
  motor2.SetSampleTimeUs(inputrate*1000);
  motor3.SetSampleTimeUs(inputrate*1000);
  motor4.SetSampleTimeUs(inputrate*1000);

  motor1.SetTunings(Kp1, Ki1, Kd1);
  motor2.SetTunings(Kp2, Ki2, Kd2);
  motor3.SetTunings(Kp3, Ki3, Kd3);
  motor4.SetTunings(Kp4, Ki4, Kd4);

  motor1.SetMode(motor1.Control::automatic);
  motor2.SetMode(motor2.Control::automatic);
  motor3.SetMode(motor3.Control::automatic);
  motor4.SetMode(motor4.Control::automatic);
}

void PID_compute(){
  motor1.Compute();
  motor2.Compute();
  motor3.Compute();
  motor4.Compute();
}

void PID_reset(){
  motor1.Reset();
  motor2.Reset();
  motor3.Reset();
  motor4.Reset();
}