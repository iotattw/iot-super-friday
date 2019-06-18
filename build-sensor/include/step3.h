
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

                // Whilst we are not connected, display the Receive Signal Strength Indicator
                Serial.printf("Signal Strength (RSSi): %i dBm\n", WiFi.RSSI());
            }
            Serial.printf("\nIP address: %s\n", WiFi.localIP().toString().c_str());
        }

        void loop() {

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

};
