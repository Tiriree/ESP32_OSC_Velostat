//////
//  OSC Example for ESP32, By Luke Woodbury- 9th Jan 2018
//  Tiri for Mimi Yin Anemone: OSC from velostat via wifi
//////
//  Set up Arduino IDE board manager https://github.com/espressif/arduino-esp32/blob/master/docs/arduino-ide/boards_manager.md
//  Download ESP32 driver https://www.silabs.com/products/development-tools/software/usb-to-uart-bridge-vcp-drivers
//  OSC library for Arduino https://github.com/tambien/oscuino
//  read more on https://learn.adafruit.com/adafruit-huzzah32-esp32-feather/overview
//  MUX https://learn.sparkfun.com/tutorials/multiplexer-breakout-hookup-guide

//Wifi and OSC stuff
#include <WiFi.h>
#include <WiFiUdp.h>
#include <OSCMessage.h>

//WIFI Settings

char ssid[] = "NETGEAR06"; //network SSID (name)
char pass[] = "perfectcar816";    //password

WiFiUDP Udp;                                // A UDP instance to let us send and receive packets over UDP
const IPAddress outIp(192, 168, 1, 4);   // remote IP of your computer
//const IPAddress outIp(192, 168, 0, 7);     // remote IP of your computer
const unsigned int outPort = 8080;          // remote port to receive OSC
const unsigned int localPort = 8000;        // local port to listen for OSC packets (actually not used for sending)
const int NUM = 12; //and this.. don't forget to change this number
const int MUX = 8; // analog input board 
const int HUZZAH = NUM - MUX; // huzzah input

//MUX pin
//Hardware Hookup: READ CAREFULLY
//Mux Breakout ----------- Arduino
//     S0 ------------------- A12(pin13)
//     S1 ------------------- A6(pin14)
//     S2 ------------------- A8(pin15)
//     Z -------------------- A2
//    VCC ------------------- 5V
//    GND ------------------- GND
//    (VEE should be connected to GND)

const int selectPins[3] = {A12, A6, A8}; // S0~A12, S1~A6(pin14), S2~A8(pin15)
const int zOutput = 5; 
const int zInput = A2; // Connect common (Z) to A2 (analog input)

long int now = 0;
int interval = 250; //sending every 0.25sec

//READ CAREFULLY
int sensorPin= A0;  // select the input pin for the potentiometer
int sensorValue = 0 ; // variable to store the value coming from the sensor
int sensorPins[] = {A3, A4, A7, A9}; // ch1~A3, ch2~A4, ch3~A7(pin32), ch4~A9(pin33)

//array for values. This tells arduino to save 12 slots for values
int sensorValues[12];

void setup() {
  //Set Serial Communication
  Serial.begin(115200);
  // Connect to WiFi network
  initWifi();

  //Mux
   // Set up the select pins as outputs:
  for (int i=0; i<3; i++)
  {
    pinMode(selectPins[i], OUTPUT);
    digitalWrite(selectPins[i], HIGH);
  }
  pinMode(zInput, INPUT); // Set up Z as an input
}

void loop() {
  checkOSCin();
  if (millis() - now > interval) {
    now = millis();
    readVelostat();
  }
}


void sendOSC(char val[]) {
  OSCMessage msg("/floor");
  msg.add(val);

  Udp.beginPacket(outIp, outPort);
  msg.send(Udp); // Send the bytes to the SLIP stream
  Udp.endPacket();  // Mark the end of the OSC Packet
  msg.empty();   // Free space occupied by message
}


void checkOSCin() {
  OSCMessage msgIn;
  int size;
  if ( (size = Udp.parsePacket()) > 0) {
    //    Serial.println("here");
    while (size--)
      msgIn.fill(Udp.read());

    if (!msgIn.hasError()) {
      msgIn.dispatch("/toArduino", dispatchAddress);
    }
  }
}


void dispatchAddress(OSCMessage &msg) {
  // Even though we are classifying, wekinator sends outputs as floats
  if (msg.isFloat(0)) {
    float val = msg.getFloat(0);
    if (val == 1) {
      Serial.println("Turning LIGH1 on");
    }
    if (val == 3) {
      Serial.println("Turning lights off");
    }
  }
}
