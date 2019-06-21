#include "BuildMonitorStep1.h"

#define NEOPIXEL_PIN 13
#define NEOPIXEL_LENGTH 8

BuildMonitorStep1::BuildMonitorStep1() : pixels(NEOPIXEL_LENGTH, NEOPIXEL_PIN, NEO_GRB + NEO_KHZ800)
{

}



void BuildMonitorStep1::setup() {
    Serial.begin(115200);
    delay(2000);
    pixels.begin();
    pixels.setBrightness(128);

    for (int i = 0; i < NEOPIXEL_LENGTH; i++)
    {
        pixels.setPixelColor(i, pixels.Color(63, 63, 63));
    }
}

void BuildMonitorStep1::loop() {
}