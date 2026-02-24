#include "Variable.h"

float value1 = 0, value2 = 0, value3 = 0;

Motor roda1(sel_fr, pwm_fr); // roda 4
Motor roda2(sel_fl, pwm_fl); // roda 2
Motor roda3(sel_bl, pwm_bl); // roda 1
Motor roda4(sel_br, pwm_br); // roda 3
// Motor roda5(rpwm_mid, lpwm_mid); // roda tengah
MotorMid roda5(rpwm_mid, lpwm_mid);

float norm_(float yaw){
  return fmod((yaw + 180), 360) - 180;
}

void setup(){
  Serial.begin(115200);
  Motor::beginPWM(20000, 12);  // satu kali di setup
  // MotorMid::beginPWM(20000, 12);  // satu kali di setup
  // PID_init();
  pinMode(LED, OUTPUT); // Configure built-in LED pin
  digitalWrite(LED, LOW); // Ensure LED is off initially
  pinMode(rpwm_mid, OUTPUT);
  pinMode(lpwm_mid, OUTPUT);

  //OBJECT CONSTRUCTING
  rangkabawah = LowerPart(sel_fr, pwm_fr, sel_fl, pwm_fl, sel_bl, pwm_bl, sel_br, pwm_br);
  rangkabawahtengah = LowerPartMid(rpwm_mid, lpwm_mid);
  calc = Kinematics(a1, a2, a3, a4, r, R);
  calc.set_ideal_value(a1_ideal, a2_ideal, a3_ideal, a4_ideal);
  calc.PPR = PPR;
  calc.init();
  calc.update_angle(0);
  // myTransfer.begin(Serial);
}

void loop(){
  // inputCommand();
  bacaKeyboard();

  receive();

  /*=============================MAIN PROGRAM=============================*/
  // MoveRobot();
  // rangkabawah.RollerMovement(2048); // Test roller movement

  if(prevCommand != rxStruct.cmd){
    if(rxStruct.cmd == 'f'){
      stop = !stop;
      digitalWrite(LED, stop ? HIGH : LOW); // Update LED state based on stop variable
    }
    else if(rxStruct.cmd == 'r'){
      reset_data = true;
    }
    else if(rxStruct.cmd == 'h'){
      roller = !roller; // Toggle roller activation
    }
    prevCommand = rxStruct.cmd;
  }

  if(!stop){
    if (millis() - input_prevmillis >= inputrate){
      MoveRobot();
      // PID_compute();
      prev_fr_tics = fr_tics; prev_fl_tics = fl_tics, prev_bl_tics = bl_tics; prev_br_tics = br_tics;
      fr_tics = ENCFR.read(); fl_tics = ENCFL.read(); bl_tics = ENCBL.read(); br_tics = ENCBR.read(); 
      prev_Timing = Timing;
      Timing = micros();
      Vreal1 = ((fr_tics - prev_fr_tics)/(((float)(Timing - prev_Timing))/1.0e6))/PPR*60.0;
      Vreal2 = ((fl_tics - prev_fl_tics)/(((float)(Timing - prev_Timing))/1.0e6))/PPR*60.0;
      Vreal3 = ((bl_tics - prev_bl_tics)/(((float)(Timing - prev_Timing))/1.0e6))/PPR*60.0;
      Vreal4 = ((br_tics - prev_br_tics)/(((float)(Timing - prev_Timing))/1.0e6))/PPR*60.0;
      Vfilt1 = Roda_1.updateEstimate(Vreal1);
      Vfilt2 = Roda_2.updateEstimate(Vreal2);
      Vfilt3 = Roda_3.updateEstimate(Vreal3);
      Vfilt4 = Roda_4.updateEstimate(Vreal4);

      // if (Serial.available() > 0){
      //   String input = Serial.readStringUntil('\n'); // membaca input hingga newline
      //   input.trim(); // menghapus spasi di awal dan akhir

      //   if (input.indexOf(' ') == -1){
      //     float singleValue = input.toFloat();
      //     if (singleValue == 1.0){
      //       rxStruct.Vx = 0.0;
      //       rxStruct.Vy = 200;
      //       rxStruct.W = 0.0;
      //     } else if (singleValue == 2.0){
      //       rxStruct.Vx = 0.0;
      //       rxStruct.Vy = 150;
      //       rxStruct.W = 0.0;
      //     } else if (singleValue == 3.0){
      //       rxStruct.Vx = 0.0;
      //       rxStruct.Vy = 100;
      //       rxStruct.W = 0.0;
      //     } else if (singleValue == 4.0){
      //       rxStruct.Vx = 0.0;
      //       rxStruct.Vy = 0.0;
      //       rxStruct.W = 0.0;
      //     } else { // jika ada spasi, berarti input terdiri dari beberapa nilai
      //       int firstSpace = input.indexOf(' ');
      //       int secondSpace = input.lastIndexOf(' ');

      //       value1 = input.substring(0, firstSpace).toFloat();
      //       value2 = input.substring(firstSpace + 1, secondSpace).toFloat();
      //       value3 = input.substring(secondSpace + 1).toFloat();

      //       motor1.SetTunings(value1, value2, value3);
      //       motor2.SetTunings(value1, value2, value3);
      //       motor3.SetTunings(value1, value2, value3);
      //       motor4.SetTunings(value1, value2, value3);
      //       Serial.print(" Kp: "); Serial.print(value1);
      //       Serial.print(" Ki: "); Serial.print(value2);
      //       Serial.print(" Kd: "); Serial.println(value3);
      //     }
      //   }
      //   Serial.print("Vxset:");
      //   Serial.print(rxStruct.Vx);
      //   Serial.print(",");
      //   Serial.print("Vyset:");
      //   Serial.print(rxStruct.Vy*10*PI/60);
      //   Serial.print(",");
      //   Serial.print("Wset:");
      //   Serial.print(rxStruct.W);
      //   Serial.print(",");
      //   Serial.print("Vx:");
      //   Serial.print(calc.Vreal[0]);
      //   Serial.print(",");
      //   Serial.print("Vy:");
      //   Serial.print(calc.Vreal[1]);
      //   Serial.print(",");
      //   Serial.print("W:");
      //   Serial.print(calc.Vreal[2]);
      //   Serial.print("");
      //   Serial.print("Vset1:");
      //   Serial.print(calc.Vwheel[0]);
      //   Serial.print(",");
      //   Serial.print("Vset2:");
      //   Serial.print(calc.Vwheel[1]);
      //   Serial.print(",");
      //   Serial.print("Vset3:");
      //   Serial.print(calc.Vwheel[2]);
      //   Serial.print(",");
      //   Serial.print("Vset4:");
      //   Serial.print(calc.Vwheel[3]);
      //   Serial.print(",");
      //   Serial.print("Vreal1:");
      //   Serial.print(Vfilt1);
      //   Serial.print(",");
      //   Serial.print("Vreal2:");
      //   Serial.print(Vfilt2);
      //   Serial.print(",");
      //   Serial.print("Vreal3:");
      //   Serial.print(Vfilt3);
      //   Serial.print(",");
      //   Serial.print("Vreal4:");
      //   Serial.print(Vfilt4);
      //   Serial.println("");
      // }

      txStruct.X = (float) calc.dist_travel[0];
      txStruct.Y = (float) calc.dist_travel[1];
      txStruct.tetha = norm_((float) calc.dist_travel[2]);
      txStruct.Vx = (float) calc.Vreal[0];
      txStruct.Vy = (float) calc.Vreal[1];
      txStruct.Wr = (float) calc.Vreal[2];
      // Serial.println(txStruct.Vx);
      // Serial.print("Vreal1: "); Serial.print(Vreal1); Serial.print(" Vfilt1: "); Serial.println(Vfilt1);

      uint16_t sendSize = 0;
      sendSize = myTransfer.txObj(txStruct, sendSize);
      myTransfer.sendData(sendSize);

      input_prevmillis = millis();
    }
  } else{
    if(reset_data){
      ENCFR.readAndReset();
      ENCFL.readAndReset();
      ENCBL.readAndReset();
      ENCBR.readAndReset();

      calc.dist_travel[0] = 0;
      calc.dist_travel[1] = 0;
      calc.dist_travel[2] = 0;
      reset_data = false;
    }
    rxStruct.Vx = 0;
    rxStruct.Vy = 0;
    rxStruct.W = 0;
    rangkabawah.Movement(0, 0, 0, 0);
  }
  
  /*=============================MAIN PROGRAM=============================*/

  /*============================DEBUG ENCODER============================*/
  // Serial.print(fr_tics);
  // Serial.print(" | ");
  // Serial.print(fl_tics);
  // Serial.print(" | ");
  // Serial.print(bl_tics);
  // Serial.print(" | ");
  // Serial.println(br_tics);

  Serial.print("cmd : ");
  Serial.print(rxStruct.cmd);
  Serial.print(" roller : ");
  Serial.print(roller);
  Serial.print(" Vx : ");
  Serial.print(rxStruct.Vx);
  Serial.print(" Vy : ");
  Serial.print(rxStruct.Vy);
  Serial.print(" W : ");
  Serial.println(rxStruct.W);
  /*============================DEBUG ENCODER============================*/
}


  // Tambahkan fungsi ini di bagian bawah untuk membaca input tombol W,A,S,D
void bacaKeyboard() {
  if (Serial.available() > 0) {
    char cmd = Serial.read();
    
    // Reset nilai tiap ada input baru
    rxStruct.Vx = 0;
    rxStruct.Vy = 0;
    rxStruct.W = 0;
    stop = false;

    // Mapping tombol keyboard ke arah vektor gerak
    switch(cmd) {
      case 'w': rxStruct.Vy = 1.0; break;  // Maju
      case 's': rxStruct.Vy = -1.0; break; // Mundur
      case 'a': rxStruct.Vx = -1.0; break; // Kiri
      case 'd': rxStruct.Vx = 1.0; break;  // Kanan
      case 'q': rxStruct.W = 1.0; break;   // Putar CCW
      case 'e': rxStruct.W = -1.0; break;  // Putar CW
      case ' ': stop = true; break;        // Spasi untuk stop
    }
  }
}



void receive(){
  if(myTransfer.available()){
    int16_t recSize = 0;
    recSize = myTransfer.rxObj(rxStruct, recSize);
  }  
}

void transfer(){
  if(millis() - timePeriode >= 15){
    int16_t sendSize = 0;
    struct __attribute__((packed)) STRUCT {
      float pwm1 = calc.Vwheel[0];//control.LX;//kinec.Vw[0];
      float pwm2 = calc.Vwheel[1];//control.LY;//kinec.Vw[1];
      float pwm3 = calc.Vwheel[2];//control.RX;//kinec.Vw[2];
      float pwm4 = calc.Vwheel[3];//control.RY;//kinec.Vw[3];
    }testStruct;

    sendSize = myTransfer.txObj(testStruct, sendSize);

    myTransfer.sendData(sendSize);
    timePeriode = millis();
  }
}

// /*========================INPUT COMMAND VIA SERIAL========================*/
// void inputCommand(){
//   if (Serial.available()) {
//     String line = Serial.readStringUntil('\n');
//     line.trim();
//     if (line.length()) {
//       // Pecah token spasi
//       const int MAXTOK = 3;
//       String tok[ MAXTOK ];
//       int count = 0, start = 0;
//       for (int i = 0; i <= line.length() && count < MAXTOK; i++) {
//         if (i == line.length() || line.charAt(i) == ' ') {
//           tok[count++] = line.substring(start, i);
//           start = i + 1;
//         }
//       }
//       // Jika tepat 3 token, coba parse tuning
//       if (count == 3 && isDigit(tok[0].charAt(0))) {
//         float p = tok[0].toFloat();
//         float i = tok[1].toFloat();
//         float d = tok[2].toFloat();
//         Kp3 = p;  Ki3 = i;  Kd3 = d; // ---------------->ganti dengan variabel yg ingin di tuning
//         motor3.SetTunings(Kp3, Ki3, Kd3);
//         Serial.print("Tunings → Kp="); Serial.print(Kp3);
//         Serial.print(" Ki="); Serial.print(Ki3);
//         Serial.print(" Kd="); Serial.println(Kd3);
//       }
//       else {
//         // Single-key command
//         char c = toupper(line.charAt(0));
//         if (c == 'Q') {
//           stop = 0;
//         }
//         else if (c == 'W') {
//           stop = 1;
        
//         }
//         else {
//           Serial.println(F("Input salah. Ketik 3 angka atau Q/W."));
//         }
//       }
//     }
//   }
// }