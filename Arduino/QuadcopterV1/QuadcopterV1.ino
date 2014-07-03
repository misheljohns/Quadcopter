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

char instrCode = 0;
int instrVal = 0;

boolean flying = false;


void setup() 
{ 
  Serial.begin(115200);  // initialize serial communication:
  Wire.begin();
  
  pinMode(ledPin, OUTPUT);  // initialize the LED pin as an output
  
  motor[0].attach(3);
  motor[1].attach(5);
  motor[2].attach(6);
  motor[3].attach(9);  // attaches the servo on pin 11 to the servo object 
  /*
  currSpeed[0] = 2000;
  currSpeed[1] = 2000;
  currSpeed[2] = 2000;
  currSpeed[3] = 2000;
  
  setSpeeds(); //set everything to 2000
  
  digitalWrite(ledPin, HIGH);
  
  delay(1000); //wait for 5 seconds
  
  //after beep beep,
  
  
  currSpeed[0] = 1000;
  currSpeed[1] = 1000;
  currSpeed[2] = 1000;
  currSpeed[3] = 1000;
  
  setSpeeds(); //set everything to 1000
  
  digitalWrite(ledPin, LOW);
  */
  
  //motor[0].writeMicroseconds(2000);
  motor[0].write(0);

  Serial.println("Attach battery");
  delay(5000);
  Serial.println(motor[0].read());
  //motor[0].writeMicroseconds(1000);
  motor[0].write(180);
  delay(1000); //wait for 3 seconds
  motor[0].write(100);
  //startFlying();
  
  
  delay(2000);
  Serial.println(motor[0].read());
  /*
  setmotorSpeed(1,1500);
  setmotorSpeed(2,1500);
  setmotorSpeed(3,1500);
  setmotorSpeed(4,1500);
  */
  /*
  currSpeed[0] = 1500;
  currSpeed[1] = 1500;
  currSpeed[2] = 1500;
  currSpeed[3] = 1500;
  
  setSpeeds(); //set everything to 2000
  
  digitalWrite(ledPin, HIGH); //hi guys, I'm ready!
  
  delay(1000); //wait for a second
  
  digitalWrite(ledPin, LOW);
  */
  //Serial.println("Starting Quadcopter");
} 
 
 
void loop() 
{ 
  
  readSensors();
  
  if(flying)
  {
    //control code here
    PIDcontrolFly();
  } 
 //only for now 
  else
  {
    startFlying();
  }
  
  
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
