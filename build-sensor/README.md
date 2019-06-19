# PlatformIO /w Clion - Getting Started

## Setup

1. Download Clion from Jetbrains: https://www.jetbrains.com/clion/download/
2. Install PlatformIO Core: https://docs.platformio.org/en/latest/installation.html

    or

		$ pip install -U platformio

3. Create project directory
4. Install Clion plugins: `File Watchers`
5. Setup Project defaults:

		$ platformio init --ide clion --board firebeetle32

## Developing

This project comes with 5 include files, each building on the last to progressively guide you
through the steps of this exercise.

You can use these examples by bringing each one into the `Main.cpp` file.

* Step 1 - Make the LED blink
* Step 2 - Add Serial monitoring
* Step 3 - Add WiFi
* Step 4 - Add MQTT
* Step 5 - Add Motion Sensor

See `include/README.md` for more details on each step.

## Running

The following platformio commands are available from the cli:

Compile the code into a runable binary:

    $ pio run

Upload the runnable binary over the serial port to the deivce:

    $ pio run --target upload


Monitor the serial ouput from the device:

    $ pio device monitor

