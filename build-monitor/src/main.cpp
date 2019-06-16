#include <Adafruit_NeoPixel.h>
#include <ArduinoJson.h>
#include "WiFi.h"
#include <HTTPClient.h>
#include <TimedAction.h>
#include "root_ca.h"
#include "secrets.h"

// const char *ROOT_CA;
// const char *WIFI_SSID;
// const char *WIFI_PASS;

#define NEOPIXEL_PIN 13
#define NEOPIXEL_LENGTH 12 

enum BuildStatus
{
  UNKNOWN,
  PASSING,
  BUILDING,
  FAILING
};

uint32_t building_colors[NEOPIXEL_LENGTH];
WiFiClient espClient;

void make_building_colors(uint32_t colors[NEOPIXEL_LENGTH])
{
  int strengths[] = {255, 127, 63, 31, 15, 7};
  int half_neopixels = NEOPIXEL_LENGTH / 2;
  for (int i = 0; i < half_neopixels; i++)
  {
    colors[i] = pixels.Color(0, 0, strengths[i]);
  }
  for (int i = half_neopixels; i < NEOPIXEL_LENGTH; i++)
  {
    colors[i] = pixels.Color(strengths[i - half_neopixels], 0, strengths[i - half_neopixels]);
  }
}

void setup_wifi()
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
    }
    delay(500);
  }
  Serial.println();
  Serial.print("Connected to ");
  Serial.println(WIFI_SSID);
  Serial.print("IP address is ");
  Serial.println(WiFi.localIP());
}

BuildStatus get_build_status()
{
  HTTPClient http;
  http.begin("https://circleci.com/api/v1.1/project/github/iotattw/example-build-project?limit=1&shallow=true", ROOT_CA);
  http.addHeader("Accept", "application/json");
  int httpCode = http.GET();
  if (httpCode != 200)
  {
    Serial.println("Error on HTTP request");
    http.end();
    return UNKNOWN;
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
    return UNKNOWN;
  }
  JsonObject last_build = doc[0];
  const char *status = last_build["status"];
  if (strcmp(status, "success") == 0)
  {
    return PASSING;
  }
  if(strcmp(status, "failed") == 0)
  {
    return FAILING;
  }
  return BUILDING;
}

void setup()
{
  Serial.begin(9600);
  delay(2000);
  setup_wifi();
  make_building_colors(building_colors);

  pixels.begin();
  pixels.setBrightness(128);
}

void show_passing()
{
  for (int i = 0; i < NEOPIXEL_LENGTH; i++)
  {
    pixels.setPixelColor(i, pixels.Color(7, 127, 7));
  }
}

void show_failing()
{
  for (int i = 0; i < NEOPIXEL_LENGTH; i++)
  {
    pixels.setPixelColor(i, pixels.Color(127, 7, 7));
  }
}

void show_building()
{
  uint32_t end = building_colors[0];
  for (int i = 0; i < NEOPIXEL_LENGTH - 1; i++)
  {
    building_colors[i] = building_colors[i + 1];
    pixels.setPixelColor(i, building_colors[i]);
  }
  building_colors[NEOPIXEL_LENGTH - 1] = end;
  pixels.setPixelColor(NEOPIXEL_LENGTH, end);
}

void show_unknown()
{
  for (int i = 0; i < NEOPIXEL_LENGTH; i++)
  {
    pixels.setPixelColor(i, pixels.Color(63, 0, 63));
  }
}

BuildStatus buildStatus = UNKNOWN;

void update_lights()
{
  switch (buildStatus)
  {
  case PASSING:
    show_passing();
    break;
  case FAILING:
    show_failing();
    break;
  case BUILDING:
    show_building();
    break;
  case UNKNOWN:
  default:
    show_unknown();
    break;
  }
  pixels.show();
}

void update_build_state() {
  buildStatus = get_build_status();
}

TimedAction light_updater = TimedAction(100, update_lights);
TimedAction build_status_updater = TimedAction(5000, update_build_state);

void loop()
{
  light_updater.check();
  build_status_updater.check();
}