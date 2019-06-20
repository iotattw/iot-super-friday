
class step3 {
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

            // Give the terminal enough time to connect
            delay(1000);
            setup_wifi();
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
