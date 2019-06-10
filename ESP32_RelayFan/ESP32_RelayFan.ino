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
const IPAddress outIp(192, 168, 1, 3);   // remote IP of your computer
//const IPAddress outIp(192, 168, 0, 7);     // remote IP of your computer
const unsigned int outPort = 8080;          // remote port to receive OSC
const unsigned int localPort = 8000;        // local port to listen for OSC packets (actually not used for sending)



long int now = 0;
int interval = 250; //sending every 0.25sec

//Fan
int relay = 13;              // Tells Arduino the relay is connected to pin 13
int values;


void setup() {
  //Set Serial Communication
  Serial.begin(115200);
  // Connect to WiFi network
  initWifi();

  pinMode(relay, OUTPUT);
}

void loop() {
  checkOSCin();
  if (millis() - now > interval) {
    now = millis();
  }
}

void sendOSC(char val[]) {
  OSCMessage msg("/fan");
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
    while (size--)
      msgIn.fill(Udp.read());

    if (!msgIn.hasError()) {
      //            Serial.print("here");
      msgIn.dispatch("/toArduinoFan", dispatchAddress);
    }
  }
}


void dispatchAddress(OSCMessage & msg) {
  if (msg.isInt(0)) {

    int val = msg.getInt(0);
    if (val == 0) {
      Serial.println("0");
    }
    else if (val == 1) {
      Serial.println("1");
    }
    // check if we had only 0 or 1
    if (val == 1 || val == 0) {
      digitalWrite(relay, val);
    }
  }
}
