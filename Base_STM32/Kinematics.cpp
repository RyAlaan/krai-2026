#include "Kinematics.h"

Kinematics::Kinematics(){
  return;
}

Kinematics::Kinematics(float a1, float a2, float a3, float a4){
  this->a1 = a1;
  this->a2 = a2;
  this->a3 = a3;
  this->a4 = a4;
  this->Vw;
}

void Kinematics::set_ideal_value(float i_a1, float i_a2, float i_a3, float i_a4){
  this->ideal_a1 = i_a1;
  this->ideal_a2 = i_a2; 
  this->ideal_a3 = i_a3; 
  this->ideal_a4 = i_a4;
}

void Kinematics::init(void){
  //Term of use = To cut the perform time of calculating trigonometric value for each time, the value is calculate once in the beginning
  this->sin_value[0] = isin(this->a1); this->sin_value[1] = isin(this->a2);
  this->sin_value[2] = isin(this->a3); this->sin_value[3] = isin(this->a4);

  this->cos_value[0] = icos(this->a1); this->cos_value[1] = icos(this->a2); 
  this->cos_value[2] = icos(this->a3); this->cos_value[3] = icos(this->a4);

  this->err_cos_value[0] = icos(this->ideal_a1-this->a1); this->err_cos_value[1] = icos(this->ideal_a2-this->a2);
  this->err_cos_value[2] = icos(this->ideal_a3-this->a3); this->err_cos_value[3] = icos(this->ideal_a4-this->a4);
}


//Kecepatan tiap roda berdasarkan kecepatan linear dan angular robot
void Kinematics::invers_kin(float Vx, float Vy, float Wr){
  Vw[0] = round((-Vx*this->sin_value[0] + Vy*this->cos_value[0] + Wr*abs(this->err_cos_value[0])));
  Vw[1] = round((-Vx*this->sin_value[1] + Vy*this->cos_value[1] + Wr*abs(this->err_cos_value[1])));
  Vw[2] = round((-Vx*this->sin_value[2] + Vy*this->cos_value[2] + Wr*abs(this->err_cos_value[2])));
  Vw[3] = round((-Vx*this->sin_value[3] + Vy*this->cos_value[3] + Wr*abs(this->err_cos_value[3])));
}