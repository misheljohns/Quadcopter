#include <Servo.h> 
#include <PID_v1.h>
#include <Wire.h>

#define FLYINGSPEED 1500
#define STOPSPEED 400

#define ACC_ZERO 353
#define ACC_GRAV 72

Servo motor[4];  // create servo object to control a servo 
                
const byte ledPin = 13; // the pin that the LED is attached to

int currSpeed[4];  //store motor speed

int accx = 0, accy = 0, accz = 0;
int rotx = 0, roty = 0, rotz = 0;

float Y = 0, P = 0, R = 0;
  
char instrCode = 0;
int instrVal = 0;

boolean flying = false;

int Xin = 0,Yin = 0,Zin = 0;


void setup() 
{ 
  digitalWrite(ledPin, LOW);
  Serial.begin(115200);  // initialize serial communication:
  Wire.begin();
  
  pinMode(ledPin, OUTPUT);  // initialize the LED pin as an output
  Serial3.begin(57600);
  
  motor[0].attach(3);
  motor[1].attach(5);
  motor[2].attach(6);
  motor[3].attach(9);  // attaches the servo on pin 11 to the servo object 
  
  currSpeed[0] = 800;
  currSpeed[1] = 800;
  currSpeed[2] = 800;
  currSpeed[3] = 800;
  
  setSpeeds(); //set everything to 800 (LOW)
  
  digitalWrite(ledPin, HIGH);
  
  delay(1000); //wait for 5 seconds
  
  //after beep beep, ready to fly
  
  startFlying();
  //Serial.println("Starting Quadcopter");
} 
 
 
void loop() 
{ 
  
  readSensors();
  PIDcontrolFly();
  
}






void PIDcontrolFly()
{
  /*
  //rot y axis, motor 1,4
  erry = accx - accz;
  //erry up, motor 4 up, motor 1 down
  speedch = Kp*errx;
  motor1sp = motor1sp - speedch;
  motor4sp = motor4sp + speedch;
  //rot y axis, motor 2,3
  */
}
