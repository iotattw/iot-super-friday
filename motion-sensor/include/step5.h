#include <ctime>

class step5 {
//    WiFiClient espClient;
//    PubSubClient client(espClient);
    const int PIR_PIN = 7;

    public:
        void setup() {

            // Configure Serial Port for monitoring
            Serial.begin(115200);

            // Configure mode of LED port
            pinMode(LED_BUILTIN, OUTPUT);

            // Configure mode of LED port
            pinMode(PIR_PIN, INPUT);

            // Start the WiFi connection
            WiFi.begin(WIFI_SSID, WIFI_PASS);

            // Check the status of Wifi before we continue
            while (WiFi.status() != WL_CONNECTED) {
                // 1 second delay between checking status
                delay(1000);
                Serial.printf("New Client. RSSi: %i dBm\n", WiFi.RSSI());
            }
            Serial.printf("\nIP address: %s\n", WiFi.localIP().toString().c_str());

            // Configure for MQTT
            IPAddress mqtt_server(10, 242, 124, 242);
            client.setServer(mqtt_server, 1883);
            client.loop();
        }

        void loop() {

            // After setup, connect to MQTT Broker
            reconnect();

            if (digitalRead(PIR_PIN)) {
                detectsMovement();
            }

            // This will switch on the LED, applying 3.3v to the pin
            digitalWrite(LED_BUILTIN, HIGH);

            // This will send text to the serial port (USB cable)
            Serial.println("LED light is on");
            delay(1000);

            // This will switch off the LED, supplying no power to the pin
            digitalWrite(LED_BUILTIN, LOW);

            // This will send text to the serial port (USB cable)
            Serial.println("LED light is off");
            delay(1000);
        }

    private:
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

        static void detectsMovement() {
            // Prepare the payload
            char result[28];
            time_t now = std::time(nullptr);
            sprintf(result, "[%ld] %s", now, "Movement detected!");

            // Prepare the topic to send the payload to
            char topic[strlen(local_hostname) + 5];
            sprintf(topic, "/%s/log", local_hostname);

            client.publish(topic, result);
        }

};
