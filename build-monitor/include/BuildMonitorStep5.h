#ifndef BUILDMONITORSTEP5_H
#define BUILDMONITORSTEP5_H

#include <Adafruit_NeoPixel.h>
#include <ArduinoJson.h>
#include "WiFi.h"
#include <HTTPClient.h>
#include "root_ca.h"
#include "secrets.h"
#include "BuildStatus.h"

class BuildMonitorStep5 {
  private:
    uint32_t building_colors[];
    WiFiClient espClient;
    Adafruit_NeoPixel pixels;
    void make_building_colors(uint32_t colors[]);
    void setup_wifi();
    BuildStatus get_build_status();
    void show_passing();
    void show_failing();
    void show_building();
    void show_unknown();
    void update_lights(BuildStatus buildStatus);

  public:
    BuildMonitorStep5();
    void setup();
    void loop();
};
#endif