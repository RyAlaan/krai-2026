#include "Header.h"
              
void setup(){
  pinMode(LED, OUTPUT);
  pinMode(rpwm, OUTPUT);
  pinMode(lpwm, OUTPUT);
  Serial.begin(115200);
  myTransfer.begin(Serial);

  kinec.set_ideal_value(a1_ideal, a2_ideal, a3_ideal, a4_ideal);
  kinec.init();
  PID_init();

  Motor::beginPWM(20000, 12);  // satu kali di setup

  LowerPart base(sel_fr, pwm_fr,   // roda-1
               sel_fl, pwm_fl,   // roda-2
               sel_bl, pwm_bl, // roda-3
               sel_br, pwm_br);
} 

void loop(){
  // inputCommand(); // for Tuning PID --> Comment if not tuning
  ReadInput();  // TX Serial
  receive(); // RX Serial

  if(prevStart != control.cmd){
    if(control.cmd == 'f'){
      stop = !stop;
    }
    prevStart = control.cmd;
  }
  if(!stop){
    MoveRobot();
    digitalWrite(LED, HIGH);
    if (millis() - samplingTimePID >= 10) {
      float dt = (millis() - samplingTimePID) / 1000.0;
      Vreal1 = (ENCFR.readAndReset() / PPR) * (60.0 / dt);
      Vreal2 = (ENCFL.readAndReset() / PPR) * (60.0 / dt);
      Vreal3 = (ENCBL.readAndReset() / PPR) * (60.0 / dt);
      Vreal4 = (ENCBR.readAndReset() / PPR) * (60.0 / dt);
      samplingTimePID = millis();
    }
    Vfilt1 = motor1.updateEstimate(Vreal1);
    Vfilt2 = motor2.updateEstimate(Vreal2);
    Vfilt3 = motor3.updateEstimate(Vreal3);
    Vfilt4 = motor4.updateEstimate(Vreal4);

    PID_compute();

  }else{
    Vx, Vy, Wr = 0;
    digitalWrite(LED, LOW);
    rangkaBawah.Movement(0, 0, 0, 0);
    kinec.Vw[0] = kinec.Vw[1] = kinec.Vw[2] = kinec.Vw[3] = 0;
    PID_reset();
    prev_Timing = 0;
    Vreal1 = 0;
    Vreal2 = 0;
    Vreal3 = 0;
    Vreal4 = 0;
    Vfilt1 = Vfilt2 = Vfilt3 = Vfilt4 = 0;
  }
  
  // Serial.print(kinec.Vw[0]);
  // Serial.print(" | ");
  // Serial.print(kinec.Vw[1]);
  // Serial.print(" | ");
  // Serial.print(kinec.Vw[2]);
  // Serial.print(" | ");
  // Serial.println(kinec.Vw[3]);

}

void ReadInput(){
  if(myTransfer.available()){
    int16_t recSize = 0;
    recSize = myTransfer.rxObj(control, recSize);
  }  
}

void receive(){
  if(millis() - timePeriode >= 15){
    int16_t sendSize = 0;
    struct __attribute__((packed)) STRUCT {
      float pwm1 = kinec.Vw[0];//control.LX;//kinec.Vw[0];
      float pwm2 = kinec.Vw[1];//control.LY;//kinec.Vw[1];
      float pwm3 = kinec.Vw[2];//control.RX;//kinec.Vw[2];
      float pwm4 = kinec.Vw[3];//control.RY;//kinec.Vw[3];
    }testStruct;

    sendSize = myTransfer.txObj(testStruct, sendSize);

    myTransfer.sendData(sendSize);
    timePeriode = millis();
  }
}

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
//         Kp1 = p;  Ki1 = i;  Kd1 = d; // ---------------->ganti dengan variabel yg ingin di tuning
//         rodaFr.SetTunings(Kp1, Ki1, Kd1);
//         Serial.print("Tunings → Kp="); Serial.print(Kp1);
//         Serial.print(" Ki="); Serial.print(Ki1);
//         Serial.print(" Kd="); Serial.println(Kd1);
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