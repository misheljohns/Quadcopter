byte gyroin[6];

void readSensors() {
  Serial.println("start readsensors");
  //read accelerometer input
  accx = analogRead(0);
  accy = analogRead(1);
  accz = analogRead(2);
  
  /*
  //read gyro input
  Wire.beginTransmission(0x68);
  Serial.println("mid1 readsensors");
  Wire.write(0x02);// X, LSB
  Serial.println("mid2 readsensors");
  Wire.requestFrom(0x68,6); //reads the data send, puts it in buffer  
  //crashes here. Why? Maybe the wiring's wrong.
  
  Serial.println("mid3 readsensors");  
  Serial.println(Wire.available());
  byte count = 0;
  while(Wire.available())   
  { 
    gyroin[count] = Wire.read(); // receive a byte as character
    count ++;
  }
    Serial.print(gyroin[count]);
  
    
  //Wire.endTransmission(); 
  Serial.println("stop readsensors");
  rotx = ((int)gyroin[1]);
  rotx <<= 8;
  rotx += ((int)gyroin[0])+ 
  Serial.print(rotx);
  */
}
