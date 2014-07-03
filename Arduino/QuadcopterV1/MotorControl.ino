#include <Servo.h> 


//Update currSpeed, then call this
void setSpeeds()
{
  for(byte motorno = 0;motorno < 4;motorno++) {
      motor[motorno].writeMicroseconds(currSpeed[motorno]);              // tell servo to go to speed 
    }
}

//Power up each motor
void setmotorSpeed(byte motorno, int motorspeed)
{
  digitalWrite(ledPin, HIGH);  //LED will be on while the speed changes
  if(motorspeed > currSpeed[motorno])
  {
    for(currSpeed[motorno] += 1; currSpeed[motorno] <= motorspeed; currSpeed[motorno] += 1)  // goes to new speed
    {                                  // in steps of 1 
      motor[motorno].writeMicroseconds(currSpeed[motorno]);              // tell servo to go to speed 
      
      delay(2);                       // waits 15ms for the servo to reach the speed 
    } 
    currSpeed[motorno] -= 1;
  }
  else if(motorspeed < currSpeed[motorno])
  {
    for(currSpeed[motorno] -= 1; currSpeed[motorno] >= motorspeed; currSpeed[motorno] -= 1)  // goes to new speed
    {                                  // in steps of 1 degree 
      motor[motorno].writeMicroseconds(currSpeed[motorno]);              // tell servo to go to speed
      
      delay(1);                       // waits 15ms for the servo to reach the speed 
    } 
    currSpeed[motorno] += 1;
  }
  digitalWrite(ledPin, LOW);
}

void startFlying() {
  digitalWrite(ledPin, HIGH); 
  Serial.println("Start Flying");
  for(currSpeed[0] += 1; currSpeed[0] <= FLYINGSPEED; currSpeed[0] += 1)  // goes to new speed
  {
    currSpeed[1] = currSpeed[0];
    currSpeed[2] = currSpeed[0];
    currSpeed[3] = currSpeed[0];
    setSpeeds();
    delay(2);                       // waits 1ms for the servo to reach the speed 
  } 
  digitalWrite(ledPin, LOW);
  flying = true;
}

void stopFlying() {
  Serial.println("Stop Flying!");
  digitalWrite(ledPin, HIGH); 
  for(currSpeed[0] -= 1; currSpeed[0] >= STOPSPEED; currSpeed[0] -= 1)  // goes to new speed
  {
    currSpeed[1] = currSpeed[0];
    currSpeed[2] = currSpeed[0];
    currSpeed[3] = currSpeed[0];
    setSpeeds();
    delay(1);                       // waits 1ms for the servo to reach the speed 
  } 
  digitalWrite(ledPin, LOW);
  flying = false;
}

