# Remote toggle

This project uses an ESP8266 module (soon an ESP32) connected to a LED light and button to act as a remote trigger.

## Components
* ESP8266 module
* LED pushbutton
* Resistors (1kΩ, 220Ω)
* Wires

<img src="remote-toggle.png" width="400"/>

With the ESP8266 module disconnected from your laptop, follow the steps in the screenshot above. It might be easiest to use a breadboard.

### Pushbutton terminals
1. Connect a wire between the `vcc`/`5v` pin of the ESP module to one terminal of the pushbutton.
2. Connect a wire between the `d1` pin of the ESP module and connect it to one end of the 1kΩ resistor.
3. Connect a wire between the `gnd` pin of the ESP module and the other end of the 1kΩ resistor.
4. Connect a wire between the empty terminal of the pushbutton to meet the end of the 1kΩ resistor that is already connected to the `d1` pin of the ESP module.

### LED terminals
1. Connect a wire between the `d2` pin of the ESP module and connect it to a terminal on the LED.
2. Connect one end of the 220Ω resistor to the wire connected to the `gnd` pin of the ESP module.
3. Connect a wire between the other end of the 220Ω resistor and the remaining empty terminal of the LED.

## Developing

After connecting the ESP8266 module to your laptop, set up a new PlatformIO project as described in the [README](../README.md#getting-started-with-platformio).

Copy `lib/secrets.h.example` to `lib/secrets.h` and populate all of the details. Do not commit this file.

Then upload `main.cpp` to the ESP8266.
