/* ---- LIBRARY --- */
#include <Wire.h>
#include <SpeedTrig.h>
#include <SimpleKalmanFilter.h>
#include <QuickPID.h>
#include "Encoder.h"
#include "SpeedTrig.h"
#include "LowerPart.h"
#include "Kinematics.h"
#include "SerialTransfer.h"
#include "Imu.h"
// #include "MotorMid.h"


// #include "LowerMid.h"

/* --- TIMINGS --- */
unsigned long input_prevmillis = 0;
uint8_t inputrate = 7; /*4 ms for 1,25 m/s 
                      10 ms for 0,5 m/s
                      20 ms for 0.25 m/s
                      to get uncertainty with 0,5 cm periode of control system
                      use this formula = (min_measurement (cm)*1000)/velocity (cm/s)
                      */

/* --- OBJECT --- */
LowerPart rangkabawah;
Kinematics calc;
Imu_handler imu;

/* --- DC MOTOR for movement  PIN --- */
//-- kanan depan (1) udah
#define sel_fr PA2
#define pwm_fr PB8
#define encA_fr PA6
#define encB_fr PB12

//kiri depan (2)
#define sel_fl PA3
#define pwm_fl PB7
#define encA_fl PA7
#define encB_fl PB13

//kiri belakang (3) udah
#define sel_bl PA4
#define pwm_bl PB6
#define encA_bl PA8
#define encB_bl PB14

//kanan belakang (4) udah
#define sel_br PA5
#define pwm_br PB9
#define encA_br PA9
#define encB_br PB15

#define LED PC13

/* --- QUADRATURE ENCODER MOTOR --- */
const float PPR = 537.6; //PPR Encoder 
Encoder_internal_state_t * Encoder::interruptArgs[];
Encoder ENCFR(encA_fr, encB_fr, PPR);
Encoder ENCFL(encA_fl, encB_fl, PPR);
Encoder ENCBL(encA_bl, encB_bl, PPR);
Encoder ENCBR(encA_br, encB_br, PPR);

/* --- SERIAL COM --- */
SerialTransfer myTransfer;