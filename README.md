# ESP32_OSC_Velostat
ESP32 Arduino communicates sensor data over OSC 

For Mimi Yin's Anemone Floor sensor 

Using Adafruit Huzzah32 [Adafruit Overview](https://learn.adafruit.com/adafruit-huzzah32-esp32-feather/overview)

## To set up the hardware

Set up Arduino IDE board manager [download](https://github.com/espressif/arduino-esp32/blob/master/docs/arduino-ide/boards_manager.md)

    Install the current upstream Arduino IDE at the 1.8 level or later. The current version is at the Arduino website.
    
    Start Arduino and open Preferences window.
    
    Enter https://dl.espressif.com/dl/package_esp32_index.json into Additional Board Manager URLs field. You can add multiple URLs, separating them with commas.
    
    Open Boards Manager from Tools > Board menu and install esp32 platform (and don't forget to select your ESP32 board from Tools > Board menu after installation).
          

[Download ESP32 driver](https://www.silabs.com/products/development-tools/software/usb-to-uart-bridge-vcp-drivers)

[OSC library for Arduino](https://github.com/tambien/oscuino)

Once installed, use the Adafruit ESP32 Feather board in the dropdown

For Upload speed, 921600 baud works great.

[OSC example](https://github.com/lwoodbury/Huzzah32OSC)


Special thanks to [Sebastian Morales](https://github.com/sebmorales/ESP32_OSC_Sensors)
