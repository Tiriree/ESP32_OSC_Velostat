///////////////////////////
//Tiri for Mimi Anemone//
///////////////////////////

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

//#define BNO055_SAMPLERATE_DELAY_MS (100)
//
//Adafruit_BNO055 bno = Adafruit_BNO055(55);

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
} Packet;


void setup() {

  // setup the radio
  radio.initialize(myFrequency, myID, myNetwork);

  // this example only uses Serial inside setup()
  // because Narcoleptic will stop Serial once used
  Serial.begin(9600);
  //  Serial.println("\nRADIO INITIALIZED");
  Serial.println("hello");


}


void loop() {

  if (Serial.available()) {
    int values = -1;
    int inByte  = Serial.read();
    if (inByte == '0') {//new Mimi string
      values = 0;
    } else if (inByte == '1') {
      values = 1;
    }
    if (values == 1 || values == 0) {
      Packet packet;
      packet.sensor0 = values;


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
  }

}
