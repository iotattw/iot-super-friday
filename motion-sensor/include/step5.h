#include <ctime>

class step5 {
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

    public:
        void setup() {

            // Configure Serial Port for monitoring
            Serial.begin(115200);

            // Configure mode of LED port
            pinMode(LED_BUILTIN, OUTPUT);

            // Configure mode of LED port
            pinMode(PIR_PIN, INPUT);

            // Give the terminal enough time to connect
            delay(1000);
            setup_wifi();

            // Configure for MQTT
            client.setServer(mqtt_server, 1883);
        }

        void loop() {
            // Ensure we're connected to the MQTT broker
            reconnect();
            client.loop();

            if (digitalRead(PIR_PIN)) {
                detectsMovement();

                // This will switch on the LED, applying 3.3v to the pin
                digitalWrite(LED_BUILTIN, HIGH);

                // This will send text to the serial port (USB cable)
                Serial.println("LED light is on");
                // Delay to give the motion sensor time to go quiet
                delay(1000);

                digitalWrite(LED_BUILTIN, LOW);
                Serial.println("LED light is off");
            }
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
