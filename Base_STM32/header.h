#include "variant_BLACKPILL_F411CE.h"
#include <FastTrig.h>
#include <QuickPID.h>
#include <SimpleKalmanFilter.h>
#include "Variable.h"
#include "LowerPart.h"
#include "Kinematics.h"
#include <Wire.h> 
#include "SerialTransfer.h"
#include "Encoder.h"

SerialTransfer myTransfer;
struct __attribute__((packed)) STRUCT {
  char cmd;
  float vx;
  float vy;  
  int Wr;
} control;

/*-----------------------Motor Pins-----------------------*/
//kanan depan (2)
#define sel_fr PA3
#define pwm_fr PB7
#define encA_fr PA7
#define encB_fr PB13

//kiri depan (1)
#define sel_fl PA4
#define pwm_fl PB6
#define encA_fl PA8
#define encB_fl PB14

//kiri belakang (4)
#define sel_bl PA5
#define pwm_bl PB9
#define encA_bl PA9
#define encB_bl PB12

//kanan belakang (3)
#define sel_br PA2
#define pwm_br PB8
#define encA_br PB6
#define encB_br PA12

#define rpwm PB0
#define lpwm PB1

#define LED PC13

/*--------------------------Object-----------------------*/
LowerPart rangkaBawah(sel_fr, pwm_fr, sel_fl, pwm_fl, sel_bl, pwm_bl, sel_br, pwm_br);
Kinematics kinec(a1_real, a2_real, a3_real, a4_real);

SimpleKalmanFilter motor1(e_mea, e_est, q);
SimpleKalmanFilter motor2(e_mea, e_est, q);
SimpleKalmanFilter motor3(e_mea, e_est, q);
SimpleKalmanFilter motor4(e_mea, e_est, q);

Encoder_internal_state_t * Encoder::interruptArgs[];
Encoder ENCFR(encA_fr, encB_fr, PPR);
Encoder ENCFL(encA_fl, encB_fl, PPR);
Encoder ENCBL(encA_bl, encB_bl, PPR);
Encoder ENCBR(encA_br, encB_br, PPR);

QuickPID rodaFr(&Vfilt1, &Output1, &kinec.Vw[0], Kp1, Ki1, Kd1,
               rodaFr.pMode::pOnError,
               rodaFr.dMode::dOnMeas,            
               rodaFr.iAwMode::iAwCondition,  
               rodaFr.Action::direct);
QuickPID rodaFl(&Vfilt2, &Output2, &kinec.Vw[1], Kp2, Ki2, Kd2,
               rodaFl.pMode::pOnError,
               rodaFl.dMode::dOnMeas,            
               rodaFl.iAwMode::iAwCondition,  
               rodaFl.Action::direct);
QuickPID rodaBl(&Vfilt3, &Output3, &kinec.Vw[2], Kp3, Ki3, Kd3,
               rodaBl.pMode::pOnError,
               rodaBl.dMode::dOnMeas,            
               rodaBl.iAwMode::iAwCondition,  
               rodaBl.Action::direct);
QuickPID rodaBr(&Vfilt4, &Output4, &kinec.Vw[3], Kp4, Ki4, Kd4,
               rodaBr.pMode::pOnError,
               rodaBr.dMode::dOnMeas,            
               rodaBr.iAwMode::iAwCondition,  
               rodaBr.Action::direct);