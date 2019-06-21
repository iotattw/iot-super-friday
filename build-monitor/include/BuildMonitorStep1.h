#ifndef BUILDMONITORSTEP1_H
#define BUILDMONITORSTEP1_H

#include <Adafruit_NeoPixel.h>
#include <ArduinoJson.h>
#include "WiFi.h"
#include <HTTPClient.h>
#include "root_ca.h"
#include "secrets.h"
#include "BuildStatus.h"

class BuildMonitorStep1 {
  private:
    Adafruit_NeoPixel pixels;
    void setup_wifi();

  public:
    BuildMonitorStep1();
    void setup();
    void loop();
};
#endif