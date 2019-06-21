#ifndef BUILDMONITORSTEP4_H
#define BUILDMONITORSTEP4_H

#include <Adafruit_NeoPixel.h>
#include <ArduinoJson.h>
#include "WiFi.h"
#include <HTTPClient.h>
#include "root_ca.h"
#include "secrets.h"
#include "BuildStatus.h"

class BuildMonitorStep4 {
  private:
    WiFiClient espClient;
    Adafruit_NeoPixel pixels;
    void setup_wifi();
    BuildStatus get_build_status();
    void show_passing();
    void show_failing();
    void show_building();
    void show_unknown();
    void update_lights(BuildStatus buildStatus);

  public:
    BuildMonitorStep4();
    void setup();
    void loop();
};
#endif