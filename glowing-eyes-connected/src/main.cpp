#include <Arduino.h>
#include <FastLED.h>
#include <PubSubClient.h>
#include "WiFi.h"
#include "secrets.h"

#define LED_PIN 18  /* This determines which pin to use */
#define NUM_LEDS 2 /* This determines the number of "eyes" */
#define DELAY 0   /* This determines the delay between setting colour values, bigger value = slower animation. */

WiFiClient espClient;
PubSubClient client(espClient);

CRGB leds[NUM_LEDS];
uint8_t brightness;


static void event_handler(char* topic, byte* payload, unsigned int length)
{
    Serial.printf("We received an event!\n");
    for (int i = 0; i < 5; ++i)
    {
        // put your main code here, to run repeatedly:
        for (float t = 0.0; t < (2 * 3.14159); t += 0.01)
        {
            brightness = (128 * sin(t)) + 128;
            for (int x = 0; x < NUM_LEDS; x++)
            {
                leds[x] = CRGB::Red;
                leds[x].fadeLightBy(brightness);
                FastLED.show();
            }
            delay(DELAY);
        }

    }
}

void setup()
{

    // Configure Serial Port for monitoring
    Serial.begin(115200);

    // Start the WiFi connection
    WiFi.mode(WIFI_STA);
    WiFi.disconnect();

    WiFi.begin(WIFI_SSID, WIFI_PASS);

    // Check the status of Wifi before we continue
    while (WiFi.status() != WL_CONNECTED) {
        // 1 second delay between checking status
        delay(1000);
        Serial.printf("Connecting to %s Signal strength: %i dBm\n", WIFI_SSID, WiFi.RSSI());
    }
    Serial.printf("\nIP address: %s\n", WiFi.localIP().toString().c_str());

    // Configure for MQTT
    client.setServer(mqtt_server, 1883);
    client.setCallback(event_handler);
    client.loop();

    // put your setup code here, to run once:
    FastLED.addLeds<NEOPIXEL, LED_PIN>(leds, NUM_LEDS);
}

static void reconnect() {
    // Loop until we're reconnected
    while (!client.connected()) {
        Serial.print("Attempting MQTT connection...");

        // Attempt to connect
        if (client.connect(local_hostname, mqtt_username, mqtt_passsword)) {
            Serial.printf("connected to broker %s\n", local_hostname);
            // Once connected, publish an announcement...
            client.publish("/tw/welcome", WiFi.localIP().toString().c_str());
        } else {
            Serial.printf("failed, rc=%i try again in 5 seconds\n", client.state());
            // Wait 5 seconds before retrying
            delay(5000);
        }
    }
}

void loop()
{
    // After setup, connect to MQTT Broker
    reconnect();
    client.subscribe("/MotionSensor/log");
    client.loop();

}
