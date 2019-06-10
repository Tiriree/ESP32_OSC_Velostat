
void readVelostat() {

 //huzzah read
//  int values[12]; //don't forget to change this
  for (int i= 0; i < HUZZAH; i++) {  
    sensorValues[i ] = analogRead(sensorPins[i]);
  }

  //Mux read
  for (byte pin = 0; pin < MUX; pin++){
    selectMuxPin(pin); // Select one at a time
    int inputValue = analogRead(A2); // and read Z
    //    Serial.print(String(inputValue) + "\t");
    sensorValues[pin+HUZZAH]= inputValue;
  }

 
  char payload[512];
//  sprintf(payload, "{\n \"state\":{\n\"floor\": [%d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d] \n }\n}", sensorValues[0] , sensorValues[1], sensorValues[2], sensorValues[3], sensorValues[4], sensorValues[5], sensorValues[6], sensorValues[7], sensorValues[8], sensorValues[9], sensorValues[10], sensorValues[11] );
    sprintf(payload, "%d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d", sensorValues[0], sensorValues[1], sensorValues[2], sensorValues[3], sensorValues[4], sensorValues[5], sensorValues[6], sensorValues[7], sensorValues[8], sensorValues[9], sensorValues[10], sensorValues[11]);
  sendOSC(payload);
  Serial.println(payload);
  Serial.println("");
}

// The selectMuxPin function sets the S0, S1, and S2 pins
// accordingly, given a pin from 0-7.
void selectMuxPin(byte pin)
{
  for (int i=0; i<3; i++)
  {
    if (pin & (1<<i))
      digitalWrite(selectPins[i], HIGH);
    else
      digitalWrite(selectPins[i], LOW);
  }
}
