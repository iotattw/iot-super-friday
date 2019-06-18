
class step2 {
    public:
        void setup() {

            // Configure Serial Port for monitoring
            Serial.begin(115200);

            // Configure mode of LED port
            pinMode(LED_BUILTIN, OUTPUT);
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
