/*
  SerialEvent occurs whenever a new data comes in the
 hardware serial RX.  This routine is run between each
 time loop() runs, so using delay inside loop can delay
 response.  Multiple bytes of data may be available.
 */
//String inputString = "";
//inputString.reserve(200);
//boolean stringComplete = false;


//change to fixed length string?

void serialEvent() {
  while (Serial.available()) {
    //char inChar = (char)Serial.read(); 
    //inputString += inChar;
    //if (inChar == '\n') { stringComplete = true; }
    //atoi() of the string
    
    
    
    //Communication format: A1234E
    //A - instruction Code
    //1234 - value
    //E - end
    
    instrCode = (char)Serial.read();
    Serial.print(instrCode);
    
    if (instrCode== 'S') { //stop!
      stopFlying();
    }
    else if (instrCode== 'E') { //stop!
      break;
    }
    else if((instrCode== 'F') && (!flying)) { //start
      startFlying();
    }
    else if (instrCode== 'X') { //Forward-Backward
      instrVal = Serial.parseInt();
            
    }
    else if (instrCode== 'Z') { //Up-Down
      instrVal = Serial.parseInt();
            
    }
    else if (instrCode== 'Y') { //Right-Left
      instrVal = Serial.parseInt();
            
    }
    else if (instrCode== 'R') { //Roll
      instrVal = Serial.parseInt();
            
    }
    else if (instrCode== 'P') { //Pitch
      instrVal = Serial.parseInt();
            
    }
    else if (instrCode== 'Q') { //Yaw
      instrVal = Serial.parseInt();
            
    }
    else if (instrCode== 'A') { //Motor1
      instrVal = Serial.parseInt();
      setSpeed(0,instrVal);      
    }
    else if (instrCode== 'B') { //Motor2
      instrVal = Serial.parseInt();
      setSpeed(1,instrVal);      
    }
    else if (instrCode== 'C') { //Motor3
      instrVal = Serial.parseInt();
      setSpeed(2,instrVal);      
    }
    else if (instrCode== 'D') { //Motor4
      instrVal = Serial.parseInt();
      setSpeed(3,instrVal);      
    }
    else if (instrCode== 'I') { //Read Accelerometer/Gyro Values
      Serial.print("Ax: \t");
      Serial.print(accx,DEC);
      Serial.print("\t Ay: \t");
      Serial.print(accy,DEC);
      Serial.print("\t Az: \t");
      Serial.print(accz,DEC);
      Serial.println("");
    }
    
  }
}

