#ifndef BUILDMONITORSTEP2_H
#define BUILDMONITORSTEP2_H

#include <Adafruit_NeoPixel.h>
#include <ArduinoJson.h>
#include "WiFi.h"
#include <HTTPClient.h>
#include "root_ca.h"
#include "secrets.h"
#include "BuildStatus.h"

class BuildMonitorStep2 {
  private:
    Adafruit_NeoPixel pixels;
    void setup_wifi();

  public:
    BuildMonitorStep2();
    void setup();
    void loop();
};
#endif