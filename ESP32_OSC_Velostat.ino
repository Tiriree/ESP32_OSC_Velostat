//////
//  OSC Example for ESP32, By Luke Woodbury- 9th Jan 2018
//  Tiri for Mimi Yin Anemone: OSC from velostat via wifi
//  With help from Sebastian Morales 
//////
//  Set up Arduino IDE board manager https://github.com/espressif/arduino-esp32/blob/master/docs/arduino-ide/boards_manager.md
//  Download ESP32 driver https://www.silabs.com/products/development-tools/software/usb-to-uart-bridge-vcp-drivers
//  OSC library for Arduino https://github.com/tambien/oscuino
//  read more on https://learn.adafruit.com/adafruit-huzzah32-esp32-feather/overview

//Wifi and OSC stuff
#include <WiFi.h>
#include <WiFiUdp.h>
#include <OSCMessage.h>

//WIFI Settings
char ssid[] = "*******"; //network SSID (name)
char pass[] = "*******";    //password

WiFiUDP Udp;                                // A UDP instance to let us send and receive packets over UDP
const IPAddress outIp(192, 168, 0, 6);     // remote IP of your computer
//const IPAddress outIp(192, 168, 0, 7);     // remote IP of your computer
const unsigned int outPort = 8080;          // remote port to receive OSC
const unsigned int localPort = 8000;        // local port to listen for OSC packets (actually not used for sending)


long int now = 0;
int interval = 250; //sending every 0.25sec

int sensorPin= A0;  // select the input pin for the potentiometer
int sensorValue = 0 ; // variable to store the value coming from the sensor
int sensorPins[] = {A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11}; // don't forget to change this

void setup() {
  //Set Serial Communication
  Serial.begin(115200);
  // Connect to WiFi network
  initWifi();
}

void loop() {
  checkOSCin();
  if (millis() - now > interval) {
    now = millis();
    readVelostat();
  }
}


void sendOSC(char val[]) {
  OSCMessage msg("/it_works");
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
