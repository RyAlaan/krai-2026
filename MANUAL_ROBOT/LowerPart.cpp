#include "LowerPart.h"
#include <cmath>   // fabsf

/* ctor default – tidak dipakai saat runtime, tapi dibutuhkan */
LowerPart::LowerPart()
: roda_1(0,0), roda_2(0,0), roda_3(0,0), roda_4(0,0)
{}

/* ctor lengkap – inisialisasi member lewat initializer-list */
LowerPart::LowerPart(byte sel_1, byte pwm_1,
                     byte sel_2, byte pwm_2,
                     byte sel_3, byte pwm_3,
                     byte sel_4, byte pwm_4)
: roda_1(sel_1, pwm_1),
  roda_2(sel_2, pwm_2),
  roda_3(sel_3, pwm_3),
  roda_4(sel_4, pwm_4)
{}

void LowerPart::Movement(float V1, float V2, float V3, float V4) {

  if (V1 > 0)       roda_1.CCW(static_cast<uint16_t>(fabsf(V1)));
  else if (V1 < 0)  roda_1.CW (static_cast<uint16_t>(fabsf(V1)));
  else              roda_1.STOP();

  if (V2 > 0)       roda_2.CCW(static_cast<uint16_t>(fabsf(V2)));
  else if (V2 < 0)  roda_2.CW (static_cast<uint16_t>(fabsf(V2)));
  else              roda_2.STOP();

  if (V3 > 0)       roda_3.CCW(static_cast<uint16_t>(fabsf(V3)));
  else if (V3 < 0)  roda_3.CW (static_cast<uint16_t>(fabsf(V3)));
  else              roda_3.STOP();

  if (V4 > 0)       roda_4.CCW(static_cast<uint16_t>(fabsf(V4)));
  else if (V4 < 0)  roda_4.CW (static_cast<uint16_t>(fabsf(V4)));
  else              roda_4.STOP();
}