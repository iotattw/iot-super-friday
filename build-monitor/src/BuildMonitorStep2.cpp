#include "BuildMonitorStep2.h"

#define NEOPIXEL_PIN 13
#define NEOPIXEL_LENGTH 12

BuildMonitorStep2::BuildMonitorStep2() : pixels(NEOPIXEL_LENGTH, NEOPIXEL_PIN, NEO_GRB + NEO_KHZ800)
{

}

void BuildMonitorStep2::setup_wifi()
{
    WiFi.mode(WIFI_STA);
    WiFi.disconnect();

    WiFi.begin(WIFI_SSID, WIFI_PASS);
    Serial.print("Connecting to ");
    Serial.print(WIFI_SSID);

    while (WiFi.status() != WL_CONNECTED)
    {
        Serial.print(".");
        if (WiFi.status() == WL_CONNECT_FAILED)
        {
            Serial.println();
            Serial.print("WiFi connection failed, re-attempting");
            WiFi.disconnect();
            WiFi.begin(WIFI_SSID, WIFI_PASS);
        }
        delay(500);
    }
    Serial.println();
    Serial.print("Connected to ");
    Serial.println(WIFI_SSID);
    Serial.print("IP address is ");
    Serial.println(WiFi.localIP());
}

void BuildMonitorStep2::setup() {
    Serial.begin(115200);
    delay(2000);
    setup_wifi();
    pixels.begin();
    pixels.setBrightness(128);

    for (int i = 0; i < NEOPIXEL_LENGTH; i++)
    {
        pixels.setPixelColor(i, pixels.Color(63, 63, 63));
    }
}

void BuildMonitorStep2::loop() {
}