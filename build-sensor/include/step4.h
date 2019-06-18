
WiFiClient espClient;
PubSubClient client(espClient);

class step4 {

    public:
        void setup() {

            // Configure Serial Port for monitoring
            Serial.begin(115200);

            // Configure mode of LED port
            pinMode(LED_BUILTIN, OUTPUT);

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

            digitalWrite(LED_BUILTIN, HIGH);
            Serial.println("LED light is on");
            delay(1000);
            digitalWrite(LED_BUILTIN, LOW);
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

};