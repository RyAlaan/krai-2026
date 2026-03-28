/*----------------------KINEMATICS---------------------------*/
//Sudut roda terhadap rangka sumbu x robot
const float a1_ideal = 45.49;
const float a2_ideal = 134.51;
const float a3_ideal = 225.49;
const float a4_ideal = 314.51;

const float a1_real = 45.36;
const float a2_real = 135.93;
const float a3_real = 227.1;
const float a4_real = 315.7;

/*----------------------Kalaman Filter---------------------*/
float e_mea = 22, q = 22, e_est = 0.01;
float Vreal1, Vreal2, Vreal3, Vreal4 = 0;
float Vfilt1, Vfilt2, Vfilt3, Vfilt4 = 0;
/*----------------------- PID --------------------------------*/
const float PPR = 537.6;
unsigned long samplingTimePID;
float Output1 = 0, Kp1 = 0, Ki1 = 0, Kd1 = 0;
float Output2 = 0, Kp2 = 0, Ki2 = 0, Kd2 = 0;
float Output3 = 0, Kp3 = 0, Ki3 = 0, Kd3 = 0;
float Output4 = 0, Kp4 = 0, Ki4 = 0, Kd4 = 0;

/*-------------------------Speed------------------------------*/
float target_linear_speed = 1800;
float target_angular_speed = 1200;
int Vx,Vy, Wr = 0;
/*-------------------------State Mekanisme------------------------------*/
bool stop = true;
bool mirror = false;
/*-------------------------Debounce------------------------------*/
char prevStart, prevL2;

volatile long timePeriode;
volatile long fr_tics, fl_tics, bl_tics, br_tics;
volatile long prev_fr_tics, prev_fl_tics, prev_bl_tics, prev_br_tics;
volatile long prev_Timing, Timing = 0;