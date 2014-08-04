const float PKp = 0.5*2;
const float PKi = 0.001; ///2/2
const float PKd = 1;

const float YKp = 0.5*2;
const float YKi = 0.001; ///2/2
const float YKd = 1;

const float RKp = 0.5*2;
const float RKi = 0.001; ///2/2
const float RKd = 1;

const float Tau = 100; //derivative signal low-pass filter crossover.

float PEk = 0; //Current Error
float PEk1 = 0; //Previous Error
float PIk = 0; //Integrated Error
float PDk = 0; //Derivative of Error
float PDk1 = 0; //Previous Derivative of Error
float PDkf = 0; // LPF of Derivative Error
float Pu = 0; // Control Output

float REk = 0; //Current Error
float REk1 = 0; //Previous Error
float RIk = 0; //Integrated Error
float RDk = 0; //Derivative of Error
float RDk1 = 0; //Previous Derivative of Error
float RDkf = 0; // LPF of Derivative Error
float Ru = 0; // Control Output

float YEk = 0; //Current Error
float YEk1 = 0; //Previous Error
float YIk = 0; //Integrated Error
float YDk = 0; //Derivative of Error
float YDk1 = 0; //Previous Derivative of Error
float YDkf = 0; // LPF of Derivative Error
float Yu = 0; // Control Output


float Pdesired = 0;
float Rdesired = 0;
float Ydesired = 0;

unsigned long t;
float dt;

int meanspeed = 1200;

void PIDControlFly()
{
  meanspeed = meanspeed + (z - 300);
  Pdesired = (x - 300)*0.01;
  Rdesired = (y - 300)*0.01;
  
  tmp = micros();
  dt = (tmp - t)/1000000;
  t = tmp();
  
  //pitch
   PEk = Pdesired - P ; //Current Error
   PIk += (PEk + PEk1)*dt; //Integrate past error //*1000/2
   PDk = (PEk - PEk1)/dt; //Error Derivative
   PDkf = 1/(1+2*Tau/(dt*1000))*(PDk + PDk1 + (2*Tau/(dt*1000)-1)*PDkf); //1st order LPF derivative
   Pu = PKp*PEk + PKi*PIk + PKd*PDkf; //PID feedback control
   PEk1 = PEk; //Update old error
   PDk1 = PDk; //Update old derivative

//roll
  REk = Rdesired - R ; //Current Error
   RIk += (REk + REk1)*dt; //Integrate past error //*1000/2
   RDk = (REk - REk1)/dt; //Error Derivative
   RDkf = 1/(1+2*Tau/(dt*1000))*(RDk + RDk1 + (2*Tau/(dt*1000)-1)*RDkf); //1st order LPF derivative
   Ru = RKp*REk + RKi*RIk + RKd*RDkf; //PID feedback control
   REk1 = REk; //Update old error
   RDk1 = RDk; //Update old derivative

//yaw
  YEk = Ydesired - Y ; //Current Error
   YIk += (YEk + YEk1)*dt; //Integrate past error //*1000/2
   YDk = (YEk - YEk1)/dt; //Error Derivative
   YDkf = 1/(1+2*Tau/(dt*1000))*(YDk + YDk1 + (2*Tau/(dt*1000)-1)*YDkf); //1st order LPF derivative
   Yu = YKp*YEk + YKi*YIk + YKd*YDkf; //PID feedback control
   YEk1 = YEk; //Update old error
   YDk1 = YDk; //Update old derivative
//pitch - m1 slower, m3 faster
//roll - m2 faster, m4 slower 
//yaw - m1,m3 faster, m2,m4 slower

  currSpeed[0] = meanspeed - Pu + Yu; //m1 + pitch + yaw
  currSpeed[1] = meanspeed + Ru - Yu; //m2 + roll - yaw
  currSpeed[2] = meanspeed + Pu + Yu; //m3 - pitch + yaw
  currSpeed[3] = meanspeed - Ru - Yu; //m4 - roll - yaw

}
