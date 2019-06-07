# ESP32_OSC_Velostat
ESP32 Arduino communicates sensor data over OSC

For Mimi Yin's Anemone Floor sensor

Using Adafruit Huzzah32 [Adafruit Overview](https://learn.adafruit.com/adafruit-huzzah32-esp32-feather/overview)

## Set up the hardware

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

# Adafruit Feather 32u4 Radio with RFM69HCW Module

## Set up the hardware

[Adafruit Feather 32u4 Overview](https://learn.adafruit.com/adafruit-feather-32u4-radio-with-rfm69hcw-module/overview)

Copy and paste the link below into the Additional Boards Manager URLs option in the Arduino IDE preferences.

    https://adafruit.github.io/arduino-board-index/package_adafruit_index.json

open the Boards Manager by navigating to the

    Tools->Board menu.

Click on the category drop down menu on the top left hand side of the window and select Contributed. You will then be able to select and install the boards supplied by the URLs added to the preferences. In the example below, we are installing support for Adafruit AVR Boards, but the same applies to all boards installed with the Board Manager.

Next,

    quit and reopen the Arduino IDE
