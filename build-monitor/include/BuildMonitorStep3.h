#ifndef BUILDMONITORSTEP3_H
#define BUILDMONITORSTEP3_H

#include <Adafruit_NeoPixel.h>
#include <ArduinoJson.h>
#include "WiFi.h"
#include <HTTPClient.h>
#include "root_ca.h"
#include "secrets.h"
#include "BuildStatus.h"

class BuildMonitorStep3 {
  private:
    WiFiClient espClient;
    Adafruit_NeoPixel pixels;
    void setup_wifi();
    BuildStatus get_build_status();
    void update_lights(BuildStatus buildStatus);

  public:
    BuildMonitorStep3();
    void setup();
    void loop();
};
#endif