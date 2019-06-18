class step3 {

    public:
        void setup() {

            // Configure Serial Port for monitoring
            Serial.begin(115200);

            // Configure mode of LED port
            pinMode(LED_BUILTIN, OUTPUT);

            // Start the WiFi connection
            WiFi.enableSTA(true);
            WiFi.begin(WIFI_SSID, WIFI_PASS);

            // Check the status of Wifi before we continue
            while (WiFi.status() != WL_CONNECTED) {
                // 1 second delay between checking status
                delay(1000);
                Serial.printf("New Client. RSSi: %i dBm\n", WiFi.RSSI());
            }
            Serial.printf("\nIP address: %s\n", WiFi.localIP().toString().c_str());
        }

        void loop() {
            digitalWrite(LED_BUILTIN, HIGH);
            Serial.println("LED light is on");
            delay(1000);
            digitalWrite(LED_BUILTIN, LOW);
            Serial.println("LED light is off");
            delay(1000);
        }

};
