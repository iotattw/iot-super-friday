#include <Adafruit_NeoPixel.h>
#include <ArduinoJson.h>
#include "WiFi.h"
#include <HTTPClient.h>
#include "root_ca.h"
#include "secrets.h"

// #include "step1.h"    // Step1 - Make the LED's blink
// #include "step2.h"    // Step2 - Add logging via Serial interface
// #include "step3.h"    // Step3 - Add WiFi connection
// #include "step4.h"    // Step4 - Add MQTT connection
#include "BuildMonitorStep5.h" // Step5 - Add Motion Sensor

BuildMonitorStep5 bulidMonitor;

void setup()
{
  bulidMonitor.setup();
};

void loop()
{
  bulidMonitor.loop();
}
