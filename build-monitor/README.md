# Build Monitor

This project uses an ESP32 module connected to a NeoPixel array to display the status of a CircleCI build (passing, building or failing).

## Components
* ESP32 module
* NeoPixel array (strip or ring)
* 3x socket-to-socket wires

<img src="build-monitor.png" width="400"/>

With the ESP32 module disconnected from your laptop

1. Connect a wire between the `gnd` pin of the ESP32 module and the `gnd` pin of the NeoPixel array.
2. Connect a wire between the `vin` pin of the ESP32 module and the `pwr` pin of the NeoPixel array.
3. Connect a wire between the `d13` pin of the ESP32 module and the `in` pin of the NeoPixel array.

## Developing

After connecting the ESP32 module to your laptop, set up a new PlatformIO project as described in the [README](../README.md#getting-started-with-platformio).