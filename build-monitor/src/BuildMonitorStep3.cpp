#include "BuildMonitorStep3.h"

#define NEOPIXEL_PIN 13
#define NEOPIXEL_LENGTH 12

BuildMonitorStep3::BuildMonitorStep3() : pixels(NEOPIXEL_LENGTH, NEOPIXEL_PIN, NEO_GRB + NEO_KHZ800)
{

}

void BuildMonitorStep3::setup_wifi()
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

BuildStatus BuildMonitorStep3::get_build_status()
{
    HTTPClient http;
    http.begin("https://circleci.com/api/v1.1/project/github/iotattw/example-build-project?limit=1&shallow=true", ROOT_CA);
    http.addHeader("Accept", "application/json");

    Serial.println("fetching build status");
    if (http.GET() != 200)
    {
        Serial.println("error on HTTP request");
        http.end();
        Serial.println("Build status unknown");
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

void BuildMonitorStep3::update_lights(BuildStatus buildStatus)
{
    switch (buildStatus)
    {
    case BUILDSTATUS_PASSING:
        Serial.println("Build passing");
        break;
    case BUILDSTATUS_FAILING:
        Serial.println("Build failing");
        break;
    case BUILDSTATUS_BUILDING:
        Serial.println("Build building");
        break;
    case BUILDSTATUS_UNKNOWN:
    default:
        Serial.println("Build unknown");
        break;
    }
    pixels.show();
}

void BuildMonitorStep3::setup() {
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

void BuildMonitorStep3::loop() {
    BuildStatus buildStatus = get_build_status();
    for (int i = 0; i < 10; ++i)
    {
        update_lights(buildStatus);
        delay(100);
    } 
}