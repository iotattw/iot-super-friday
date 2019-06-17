//
// Created by Timothy Findlay on 2019-06-17.
//

#include <Arduino.h>
#include "WiFi.h"
#include <PubSubClient.h>

#include "step1.h"    // Step1 - Make the LED's blink
#include "step2.h"    // Step2 - Add logging via Serial interface
#include "step3.h"    // Step3 - Add WiFi connection
#include "step4.h"    // Step4 - Add MQTT connection
#include "step5.h"    // Step5 - Add Motion Sensor

step5 o;

void setup() {
    o.setup();
};

void loop() {
    o.loop();
}