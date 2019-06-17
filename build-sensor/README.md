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
Step 1 - Create CPP file with loop() + setup()
* Add to `platformio.ini`
```
upload_speed = 230400
upload_port = /dev/cu.usbserial-1420
```

Step 2 - Add Serial monitoring
* Add platformio.ini
```
monitor_speed = 115200
```
* Add to command line: `platformio device monitor`

Step 3 - Add WiFi


Step 4 - Add MQTT
* Add platformio.ini
```
lib_deps = 89
```

Step 5 - Add Motion Sensor
* Add to platformio.ini
	monitor_speed = 115200
