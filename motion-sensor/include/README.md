# Motion Sensor Steps
This folder includes example code for the workshop.

For an overview of the workshop goals see [motion-sensor](../README.md)

In this folder you will find:

### step1.h:

Basic example to configure 1 IO pin and switch the built in LED on/off.
This is configured with a 1 second delays (1000ms) between each change of state.
There is no other libraries needed other the standard `Arduino.h`
To upload and run this you should check the following is configured in `platformio.ini`:

    upload_speed = 230400
    upload_port = /dev/cu.usbserial-1420

### step2.h:

Extending on step1.h this adds the use of the Serial output. This is really only useful
if you have the device plugged into a machine which is monitoring the port.
This configured the port speed to 115200. This should match the configured monitoring baud
rate in `platformio.ini`:

    monitor_speed = 115200

After uploading this, you can use the Serial port monitor in platform io like so:

    $ pio device monitor

### step3.h

Extending on step2.h this now adds a dependency on WiFi.h and requires credentials (kept in secrets.h)
The secrets.h must configure constants:

    ssid
    password

These are used to establish a connection to a wireless network. The IP address is sent via the Serial output
configured in step2.

### step4.h

Extending on step3.h this now adds a dependency on PubSubClient.h which provides a library to connect to an
MQTT broker over the TCP/IP connection established in step3.

This requires the following constants to be configured in secrets.h

    local_hostname
    mqtt_username
    mqtt_passsword

These are used to authenticate with the MQTT broker and publish the devices IP address to the topic `/tw/welcome`

### step5.h

Extending on step4.h this now integrates reading from the GPIO pin to transmit a message to the MQTT broker.
There is no additional configuration or dependencies from this step.
To avoid colliding messages, the topic name is dynamic and will send the payload to a topic unique to each device.
