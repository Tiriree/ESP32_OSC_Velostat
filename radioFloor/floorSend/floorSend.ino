///////////////////////////
//ANEMONE
///////////////////////////

// https://learn.adafruit.com/adafruit-feather-32u4-radio-with-rfm69hcw-module/pinouts
// https://learn.adafruit.com/adafruit-bno055-absolute-orientation-sensor/overview


/*

  This sketch demonstrates a simple wireless low-power sensor node,
  sending packets to the receiver on this network.
  To make parsing packets easier, data is sent using the C++ struct.
  This allows both sender and receiver to read and write to the packet
  using the familiar object-dot-variable syntax.

  See the "wiring_rfm69.png" for how to hookup the circuit.

  To complete the example, run the "sensor_receive.ino" sketch
  on another Arduino with an RFm69 connected

  Be sure you have downloaded and installed the library used here:

    RFm69 Library: https://github.com/lowpowerlab/rfm69
    Narcoleptic Library: https://code.google.com/p/narcoleptic/downloads/list

  Created 24 March 2015
  By Andy Sigler
  special thanks to Aaron Parsekian and Sebastian Morales

*/



#include <RFM69.h>
#include <SPI.h> // the RFM69 library uses SPI
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>

#define BNO055_SAMPLERATE_DELAY_MS (100)

Adafruit_BNO055 bno = Adafruit_BNO055(55);

#define myFrequency RF69_915MHZ // or RF69_433MHZ (check your radio)
#define IS_RFM69HCW   true
/* for Feather 32u4 */
#define RFM69_CS      8
#define RFM69_IRQ     7
#define RFM69_IRQN    4  // Pin 7 is IRQ 4!
#define RFM69_RST     4

RFM69 radio = RFM69(RFM69_CS, RFM69_IRQ, IS_RFM69HCW, RFM69_IRQN);

#define myFrequency RF69_915MHZ // or RF69_433MHZ (check your radio)
int myNetwork = 1; // radios must share the same network (0-255)
int myID = 6; // radios should be given unique ID's (0-254, 255 = BROADCAST)

int hubID = 5; // the receiver for all sensor nodes in this example

// instead of sending a string, we can send a struct
// this struct must be shared between all nodes
typedef struct {
  int sensor0;
  int sensor1;
  int sensor2;
  int sensor3;
  int sensor4;
  int sensor5;
  int sensor6;
  int sensor7;
  int sensor8;
  int sensor9;
} Packet;


///////////////////////////
///////////////////////////
///////////////////////////


void setup() {

  // setup the radio
  radio.initialize(myFrequency, myID, myNetwork);

  // this example only uses Serial inside setup()
  // because Narcoleptic will stop Serial once used
  Serial.begin(9600);
  Serial.println("\nRADIO INITIALIZED");
  Serial.println("Sending sensor values");


}

///////////////////////////
///////////////////////////
///////////////////////////

void loop() {
  // create new instance of our Packet struct
  int sensorValue = analogRead(A0);
  int sensorValue1 = analogRead(A1);
  int sensorValue2 = analogRead(A2);
  int sensorValue3 = analogRead(A3);
  int sensorValue4 = analogRead(A4);
  int sensorValue5 = analogRead(A5);
  int sensorValue6 = analogRead(A7);
  int sensorValue7 = analogRead(A9);
  int sensorValue8 = analogRead(A10);
  int sensorValue9 = analogRead(A11);

  Packet packet;

  packet.sensor0 = sensorValue;
  packet.sensor1 = sensorValue1;
  packet.sensor2 = sensorValue2;
  packet.sensor3 = sensorValue3;
  packet.sensor4 = sensorValue4;
  packet.sensor5 = sensorValue5;
  packet.sensor6 = sensorValue6;
  packet.sensor7 = sensorValue7;
  packet.sensor8 = sensorValue8;
  packet.sensor9 = sensorValue9;


  Serial.print(packet.sensor0);
  Serial.print(",");
  Serial.print(packet.sensor1);
  Serial.print(",");
  Serial.print(packet.sensor2);
  Serial.print(",");
  Serial.print(packet.sensor3);
  Serial.print(",");
  Serial.print(packet.sensor4);
  Serial.print(",");
  Serial.print(packet.sensor5);
  Serial.print(",");
  Serial.print(packet.sensor6);
  Serial.print(",");
  Serial.print(packet.sensor7);
  Serial.print(",");
  Serial.print(packet.sensor8);
  Serial.print(",");
  Serial.println(packet.sensor9);


  int numberOfRetries = 3;

  // send reliable packet to the hub
  // notice the & next to packet when sending a struct
  boolean gotACK = radio.sendWithRetry(hubID,  &packet, sizeof(packet), numberOfRetries);

  if (gotACK) {
    //    Serial.println("got unknown packet!");
  }
  else {
    //    Serial.println("failed acknowledgment");
  }
  delay(100);
}

///////////////////////////
///////////////////////////
///////////////////////////
