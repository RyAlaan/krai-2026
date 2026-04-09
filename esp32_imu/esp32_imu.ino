
#include <basicMPU6050.h>
#include <imuFilter.h>
#include <SerialTransfer.h>
#define INPUT_INTERVAL 7 // dipilih setelah melakukan frequency sampling, periode program adalah 6.37ms
                         // sehingga periode minimal adalah math.ceil(6.37) = 7
float deg2rad = PI / 180;
SerialTransfer myTransfer;

unsigned long long prev = 0;
unsigned long long curr = 0;

struct __attribute__ ((packed)) STRUCTTX {
  float yaw;
  float pitch;
  float roll;
  float gz; // perbandingan antara ax: ay : az : ax
  float ax; // satuan g
  float ay;
  float az;
} txStruct;

#define LP_FILTER 3 
#define GYRO_SENS 0 
#define ACCEL_SENS 0 
#define ADDRESS_A0 LOW 

constexpr int AX_OFFSET = 0;
constexpr int AY_OFFSET = 0;
constexpr int AZ_OFFSET = 0;
basicMPU6050<LP_FILTER, GYRO_SENS, ACCEL_SENS, ADDRESS_A0,
              AX_OFFSET, AY_OFFSET, AZ_OFFSET
              >imu;

const float driftCompensate = 0.98; const int sampling = 32;
int countUP, countDN = 0;
float gx, gy, gz;
float prevgx, prevgy, prevgz = 0;
float gmean[3] = {0,0,0};

imuFilter fusion;
#define GAIN 0.5 
#define SD_ACCEL 0.2
#define FUSION true 

void setup() {
 Serial.begin(115200);
 myTransfer.begin(Serial);
 Wire.begin(8,9);
 imu.setup();
 imu.setBias();
#if FUSION
 fusion.setup( imu.ax(), imu.ay(), imu.az() );
#else
 fusion.setup();
#endif
}

void loop() {
  curr = millis();
  if (curr - prev >= INPUT_INTERVAL) {
    gx = drift_elim(imu.gx(), prevgx, 0);
    gy = drift_elim(imu.gy(), prevgy, 1);
    gz = drift_elim(imu.gz(), prevgz, 2);
    prevgx = imu.gx();
    prevgy = imu.gy();
    prevgz = imu.gz();

    fusion.update( gx, gy, gz, imu.ax(), imu.ay(), imu.az() );    

    txStruct.yaw = fusion.yaw(); //  * deg2rad
    txStruct.pitch = fusion.pitch();
    txStruct.roll = fusion.roll();
    txStruct.gz = gz;
    txStruct.ax = imu.ax();
    txStruct.ay = imu.ay();
    txStruct.az = imu.az();
    Serial.print(txStruct.yaw);
    Serial.print(" ");
    Serial.print(txStruct.pitch);
    Serial.print(" ");
    Serial.print(txStruct.roll);
    Serial.print(" ");
    Serial.print(txStruct.gz);
    Serial.print(" ");
    Serial.print(txStruct.ax);
    Serial.print(" ");
    Serial.println(txStruct.ay);
    Serial.print(" ");
    Serial.println(txStruct.az);
    uint16_t sendSize = 0;
    sendSize = myTransfer.txObj(txStruct, sendSize);
    myTransfer.sendData(sendSize);
    prev = curr;
  }
} 

float drift_elim(float raw, float prevraw, int idx){
  float mean = 0;
  if(abs(raw) <= 0.005){
    if(abs(raw)*driftCompensate >= abs(prevraw)){
      if(countUP >= sampling){
        countUP = 0;
        mean = gmean[idx]/sampling;
        gmean[idx] = 0;
      } else{
        countDN = 0;
        countUP++;
        gmean[idx] += raw;
      }
    } else if(abs(raw)*driftCompensate <= abs(prevraw)){
      if(countDN >= sampling){
        countDN = 0;
        mean = gmean[idx]/sampling;
        gmean[idx] = 0;
      } else{
        countUP = 0;
        countDN++;
        gmean[idx] += raw;
      }
    } else{
      countUP = 0;
      countDN = 0;
      gmean[idx] = 0;
    }
  } else{
    countUP = 0;
    countDN = 0;
    mean = raw;
  }
  return mean;
}