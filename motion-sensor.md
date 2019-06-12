# Motion Sensor

This project uses an ESP32 module connected to a motion sensor to send a "motion detected" message when it detects activity, and then an "all clear" message after a certain period of inactivity.

## Components
* ESP32 module
* Motion sensor
* 3x socket-to-socket wires
* (optional) battery pack

You should have something like this:  
*(picture of Motion Sensor components laid out on a table)*

## Hardware Steps

![Motion Sensor](motion-sensor.png)

With the ESP32 module disconnected from your laptop:

1. Connect a wire between the `gnd` pin of the ESP32 module and the `gnd` pin of the motion sensor.
2. Connect a wire between the `vcc`/`5v` pin of the ESP32 module to the `vcc`/`5v` pin of the motion sensor.
3. Connect a wire between the `d4` pin of the ESP32 module to the `out` pin of the motion sensor.

## Software steps

After connecting the ESP32 module to your laptop:

1. Set up a new Platform․IO project as described in the [README](README.md#getting-started)
2. Set up the `d4` pin as an "in" pin. Put the motion sensor inside an enclosed container. Use the serial monitor to view the state of the pin when you move your hand in front of the motion sensor.
3. Use the PIO Home "Libraries" tab to search for and download the [PubSubClient](https://pubsubclient.knolleary.net) library. Have a look at the "mqtt_esp8266" example on the "Examples" tab.
4. Include the library in your source code (`#include "PubSubClient.h"`) and test it out by sending messages to the "hello-world" topic a at `mqtt.svr.ip.addr`.
5. Work out how you'll use the `setup` and `loop` methods to detect motion and send messages for "motion detected" and "all clear" events.