#include "BuildMonitorStep4.h"

#define NEOPIXEL_PIN 13
#define NEOPIXEL_LENGTH 12

BuildMonitorStep4::BuildMonitorStep4() : pixels(NEOPIXEL_LENGTH, NEOPIXEL_PIN, NEO_GRB + NEO_KHZ800)
{

}

void BuildMonitorStep4::setup_wifi()
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

BuildStatus BuildMonitorStep4::get_build_status()
{
    HTTPClient http;
    http.begin("https://circleci.com/api/v1.1/project/github/iotattw/example-build-project?limit=1&shallow=true", ROOT_CA);
    http.addHeader("Accept", "application/json");

    Serial.println("fetching build status");
    if (http.GET() != 200)
    {
        Serial.println("error on HTTP request");
        http.end();
        return BUILDSTATUS_UNKNOWN;
    }
    char *payload = const_cast<char *>(http.getString().c_str());
    http.end();

    // Use arduinojson.org/v6/assistant to compute the capacity.
    const size_t capacity = 49 * JSON_ARRAY_SIZE(0) + 11 * JSON_ARRAY_SIZE(1) + JSON_ARRAY_SIZE(12) + 12 * JSON_OBJECT_SIZE(0) + 12 * JSON_OBJECT_SIZE(1) + 11 * JSON_OBJECT_SIZE(3) + 12 * JSON_OBJECT_SIZE(6) + 12 * JSON_OBJECT_SIZE(7) + 11 * JSON_OBJECT_SIZE(13) + 12 * JSON_OBJECT_SIZE(57) + 25500;

    DynamicJsonDocument doc(capacity);

    DeserializationError error = deserializeJson(doc, payload);
    if (error)
    {
        Serial.print("deserializeJson() failed: ");
        Serial.println(error.c_str());
        return BUILDSTATUS_UNKNOWN;
    }
    JsonObject last_build = doc[0];
    const char *status = last_build["status"];
    if (strcmp(status, "success") == 0)
    {
        return BUILDSTATUS_PASSING;
    }
    if (strcmp(status, "failed") == 0)
    {
        return BUILDSTATUS_FAILING;
    }
    return BUILDSTATUS_BUILDING;
}

void BuildMonitorStep4::show_passing()
{
    for (int i = 0; i < NEOPIXEL_LENGTH; i++)
    {
        pixels.setPixelColor(i, pixels.Color(7, 127, 7));
    }
}

void BuildMonitorStep4::show_failing()
{
    for (int i = 0; i < NEOPIXEL_LENGTH; i++)
    {
        pixels.setPixelColor(i, pixels.Color(127, 7, 7));
    }
}

void BuildMonitorStep4::show_building()
{
    for (int i = 0; i < NEOPIXEL_LENGTH; i++)
    {
        pixels.setPixelColor(i, pixels.Color(7, 7, 127));
    }
}

void BuildMonitorStep4::show_unknown()
{
    for (int i = 0; i < NEOPIXEL_LENGTH; i++)
    {
        pixels.setPixelColor(i, pixels.Color(63, 0, 63));
    }
}

void BuildMonitorStep4::update_lights(BuildStatus buildStatus)
{
    switch (buildStatus)
    {
    case BUILDSTATUS_PASSING:
        Serial.println("Build passing");
        show_passing();
        break;
    case BUILDSTATUS_FAILING:
        Serial.println("Build failing");
        show_failing();
        break;
    case BUILDSTATUS_BUILDING:
        Serial.println("Build building");
        show_building();
        break;
    case BUILDSTATUS_UNKNOWN:
    default:
        Serial.println("Build unknown");
        show_unknown();
        break;
    }
    pixels.show();
}

void BuildMonitorStep4::setup() {
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

void BuildMonitorStep4::loop() {
    BuildStatus buildStatus = get_build_status();
    for (int i = 0; i < 10; ++i)
    {
        update_lights(buildStatus);
        delay(100);
    } 
}