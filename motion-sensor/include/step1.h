
class step1 {
    public:
        void setup() {

            // Configure mode of LED port
            pinMode(LED_BUILTIN, OUTPUT);
        }

        void loop() {

            // This will switch on the LED, applying 3.3v to the pin
            digitalWrite(LED_BUILTIN, HIGH);
            delay(1000);

            // This will switch off the LED, supplying no power to the pin
            digitalWrite(LED_BUILTIN, LOW);
            delay(1000);
        }

};
