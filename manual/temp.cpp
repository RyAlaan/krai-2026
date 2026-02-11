// // manual
// #include <Arduino.h>
// #include <math.h>

// // pin motor-encoder
// #define enc1A PA6
// #define enc1B PB12
// #define enc2A PA7
// #define enc2B PB13
// #define enc3A PA8
// #define enc3B PB14
// #define enc4A PA9
// #define enc4B PB15

// // pin encoder external
// #define encxA PB0
// #define encxB PB1
// #define encyA PC13
// #define encyB PC14

// // PPR 
// #define pprMotor 134.0
// #define pprEnc 600.0

// // Radius Motor & Encoder
// float radiusMotor = 0.05;
// float radiusEnc = 0.0275;

// // angle motor
// float angMotor1 = 45.21 * (PI/180);
// float angMotor2 = 135.21 * (PI/180);
// float angMotor3 = 225.21 * (PI/180);
// float angMotor4 = 315.21 * (PI/180);

// // angle encoder
// float angEncX = 270 * (PI/180);
// float angEncY = 180 * (PI/180);

// // Motor & encoder radius
// float distanceMotor = 32.8873;
// float distanceY = 34.75;
// float distanceX = 34.5;

// volatile int pulseCount1 = 0, pulseCount2 = 0, pulseCount3 = 0, pulseCount4 = 0, pulseCountX = 0, pulseCountY = 0;
// unsigned long prevTime = 0;
// long prevPulse1 = 0, prevPulse2 = 0, prevPulse3 = 0, prevPulse4 = 0, prevPulseX =  0, prevPulseY = 0;
// float velocity1 = 0, velocity2 = 0, velocity3 = 0, velocity4 = 0, velocityX = 0, velocityY = 0;
// float Vx = 0, Vy = 0, Omega = 0;

// // Accumulated distances
// float xDistance = 0.0;
// float yDistance = 0.0;
// float zDistance = 0.0;

// // perimeter motor & encoder
// float perimeterMotor = 2 * PI * radiusMotor;
// float perimeterEnc = 2 * PI * radiusEnc;

// // Variables for controlling print interval
// unsigned long prevPrintTime = 0;
// unsigned long printDelay = 100000; // 100ms in microseconds = 0.1 s

// // =================================================== Forward Kinematics
// float getCombinedVelocityX(
//     float Vw1, float angle1, float Vw2, float angle2,
//     float Vw3, float angle3, float Vw4, float angle4,
//     float radiusMotor, float Venc1, float alpha) {

//   float motorVx = (radiusMotor / 4) * (-sin(angle1) * Vw1 - sin(angle2) * Vw2 - sin(angle3) * Vw3 - sin(angle4) * Vw4);
//   float encVx = Venc1;
//   return alpha * motorVx + (1 - alpha) * encVx;
// }

// float getCombinedVelocityY(
//     float Vw1, float angle1, float Vw2, float angle2,
//     float Vw3, float angle3, float Vw4, float angle4,
//     float radiusMotor, float Venc2, float alpha) {

//   float motorVy = (radiusMotor / 4) * (cos(angle1) * Vw1 + cos(angle2) * Vw2 + cos(angle3) * Vw3 + cos(angle4) * Vw4);
//   float encVy = Venc2;
//   return alpha * motorVy + (1 - alpha) * encVy;
// }

// float getOmega(float Vw1, float Vw2, float Vw3, float Vw4, float radiusMotor, float distanceMotor) {
//   return (radiusMotor / (4 * distanceMotor)) * (Vw1 + Vw2 + Vw3 + Vw4);
// }
// // ===================================================

// void setup() {
//   Serial.begin(115200);
  
//   // pin motor-encoder
//   pinMode(enc1A, INPUT_PULLUP);
//   pinMode(enc1B, INPUT_PULLUP);
//   pinMode(enc2A, INPUT_PULLUP);
//   pinMode(enc2B, INPUT_PULLUP);
//   pinMode(enc3A, INPUT_PULLUP);
//   pinMode(enc3B, INPUT_PULLUP);
//   pinMode(enc4A, INPUT_PULLUP);
//   pinMode(enc4B, INPUT_PULLUP);

//   // pin encoder external
//   pinMode(encxA, INPUT_PULLUP);
//   pinMode(encxB, INPUT_PULLUP);
//   pinMode(encyA, INPUT_PULLUP);
//   pinMode(encyB, INPUT_PULLUP);

//   // Attach interrupts for each encoder
//   attachInterrupt(digitalPinToInterrupt(enc1A), updatePulse1, RISING);
//   attachInterrupt(digitalPinToInterrupt(enc2A), updatePulse2, RISING);
//   attachInterrupt(digitalPinToInterrupt(enc3A), updatePulse3, RISING);
//   attachInterrupt(digitalPinToInterrupt(enc4A), updatePulse4, RISING);

//   attachInterrupt(digitalPinToInterrupt(encxA), updatePulseX, RISING);
//   attachInterrupt(digitalPinToInterrupt(encyA), updatePulseY, RISING);
// }

// void updatePulse1() {
//   int stateB = digitalRead(enc1B);
//   pulseCount1 += (stateB > 0) ? 1 : -1;
// }

// void updatePulse2() {
//   int stateB = digitalRead(enc2B);
//   pulseCount2 += (stateB > 0) ? 1 : -1;
// }

// void updatePulse3() {
//   int stateB = digitalRead(enc3B);
//   pulseCount3 += (stateB > 0) ? 1 : -1;
// }

// void updatePulse4() {
//   int stateB = digitalRead(enc4B);
//   pulseCount4 += (stateB > 0) ? 1 : -1;
// }

// void updatePulseX() {
//   int stateB = digitalRead(encxB);
//   pulseCountX += (stateB > 0) ? 1 : -1;
// }

// void updatePulseY() {
//   int stateB = digitalRead(encyB);
//   pulseCountY += (stateB > 0) ? 1 : -1;
// }

// void loop() {
//   unsigned long currTime = micros();
//   unsigned long deltaT = (currTime - prevTime)/1.0e6;
//   prevTime = currTime;
//   if (currTime < prevTime) { // Handle overflow
//     deltaT = (4294967295 - prevTime + currTime + 1); // 2^32 - 1
//   }
//   long currPulse1 = pulseCount1;
//   long currPulse2 = pulseCount2;
//   long currPulse3 = pulseCount3;
//   long currPulse4 = pulseCount4;
//   long currPulseX = pulseCountX;
//   long currPulseY = pulseCountY;

//   long deltaPulse1 = currPulse1 - prevPulse1;
//   long deltaPulse2 = currPulse2 - prevPulse2;
//   long deltaPulse3 = currPulse3 - prevPulse3;
//   long deltaPulse4 = currPulse4 - prevPulse4;

//   long deltaPulseX = currPulseX - prevPulseX;
//   long deltaPulseY = currPulseY - prevPulseY;

//   // if (deltaT > 0 && deltaT < 1000000) { // Ignore invalid deltaT values
//   //   velocityFr = (deltaPulse1 / deltaT) * (1 / pprMotor) * perimeterMotor;
//   //   velocityFl = (deltaPulse2 / deltaT) * (1 / pprMotor) * perimeterMotor;
//   //   velocityBr = (deltaPulse3 / deltaT) * (1 / pprMotor) * perimeterMotor;
//   //   velocityBl = (deltaPulse4 / deltaT) * (1 / pprMotor) * perimeterMotor;

//   //   velocityX = (deltaPulseX / deltaT) * (1 / pprEnc) * perimeterEnc;
//   //   velocityY = (deltaPulseY / deltaT) * (1 / pprEnc) * perimeterEnc;
//   // }

//   velocity1 = (deltaPulse1 / deltaT) * (1/pprMotor) * perimeterMotor;
//   velocity2 = (deltaPulse2 / deltaT) * (1/pprMotor) * perimeterMotor;
//   velocity3 = (deltaPulse3 / deltaT) * (1/pprMotor) * perimeterMotor;
//   velocity4 = (deltaPulse4 / deltaT) * (1/pprMotor) * perimeterMotor;

//   velocityX = (deltaPulseX / deltaT) * (1 / pprEnc) * perimeterEnc;
//   velocityY = (deltaPulseY / deltaT) * (1 / pprEnc) * perimeterEnc;

//   // if (deltaPulseX < 0) {
//   //   velocityX = -velocityX;
//   // }

//   Vx = getCombinedVelocityX(velocity1, angMotor1, velocity2, angMotor2, velocity3, angMotor3, velocity4, angMotor4, radiusMotor, velocityX, 0.5);

//   Vy = getCombinedVelocityY(velocity1, angMotor1, velocity2, angMotor2, velocity3, angMotor3, velocity4, angMotor4, radiusMotor, velocityY, 0.5);

//   Omega = getOmega(velocity1, velocity2, velocity3, velocity4, radiusMotor, distanceMotor);

//   // Accumulate distances
//   xDistance += Vx * (deltaT / 1000000); // Convert deltaT to seconds
//   yDistance += Vy * (deltaT / 1000000);
//   zDistance += Omega * (deltaT / 1000000);

//   if (currTime - prevPrintTime >= printDelay) {
//       Serial.print("Vx: ");
//       Serial.print(Vx);
//       Serial.print(" || ");
//       Serial.print(" Vy: ");
//       Serial.print(Vy);
//       Serial.print(" || ");
//       Serial.print(" Omega: ");
//       Serial.println(Omega);

//       // Debug
//       // Serial.print("Delta Pulse 1: ");
//       // Serial.println(deltaPulse1);
//       // Serial.print("CurrPulse1 : ");
//       // Serial.println(currPulse1);
//       // Serial.print("prevPulse1 : ");
//       // Serial.println(prevPulse1);

//       prevPrintTime = currTime; // Update the previous print time
//   }
  
//   prevPulse1 = currPulse1;
//   prevPulse2 = currPulse2;
//   prevPulse3 = currPulse3;
//   prevPulse4 = currPulse4;
//   prevPulseX = currPulseX;
//   prevPulseY = currPulseY;
// }