#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include "secrets.h"

#define LED_BUILTIN 2
#define LED_CUSTOM 4
#define BUTTON_PIN 5
#define PIR_PIN 13

WiFiClient espClient;
PubSubClient client(espClient);
int led = 0;
int press = 0;

void callback(const char *topic, byte *payload, unsigned int length)
{
  Serial.print("Message[");
  int i = 0;
  for (i = 0; i < length; i++)
  {
    Serial.print((char)payload[i]);
  }
  Serial.println("] ");
  // Switch on the LED if an 1 was received as first character
  if ((char)payload[0] == '1')
  {
    led = 1;
  }
  if ((char)payload[0] == '0')
  {
    led = 0;
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

static void reconnect()
{

  // Loop until we're reconnected
  while (!client.connected())
  {
    Serial.print("Attempting MQTT connection...");

    // Attempt to connect
    if (client.connect(local_hostname))
    {
      Serial.printf("connected to broker %s\n", local_hostname);
      client.subscribe("/remote_switch/in");
      client.setCallback(callback);
    }
    else
    {
      Serial.printf("failed, rc=%i try again in 5 seconds\n", client.state());
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void setup()
{
  Serial.begin(115200);

  // pinMode(LED_BUILTIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT);
  pinMode(LED_CUSTOM, OUTPUT);
  delay(1000);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
}

void loop()
{
  // Ensure we're connected to the MQTT broker
  reconnect();
  client.loop();

  press = digitalRead(BUTTON_PIN);
  digitalWrite(LED_CUSTOM, led == 0 ? LOW : HIGH);

  if (press == HIGH)
  {
    client.publish("/remote_switch/out", "1");
    delay(500);
  }
  delay(100);
}