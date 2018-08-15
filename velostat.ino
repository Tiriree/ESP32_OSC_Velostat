
void readVelostat() {
  sensorValue = analogRead(sensorPin);
  int values[12]; //don't forget to change this 
  for (int i = 0; i < 12; i++) {  //and this.. don't forget to change this number
    values[i] = analogRead(sensorPins[i]);
  }
  char payload[512];
  sprintf(payload, "{\n \"state\":{\n\"floor\": [%d, %d, %d, %d, %d, %d, %d, %d] \n }\n}", values[0] , values[1], values[2], values[3], values[4], values[5], values[6], values[7] );
  sendOSC(payload);
  Serial.println(payload);
  Serial.println("");
}
