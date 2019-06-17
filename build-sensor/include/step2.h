//
// Created by Timothy Findlay on 2019-06-17.
//

#ifndef IOT_SUPER_FRIDAY_SAMPLES_STEP2_H
#define IOT_SUPER_FRIDAY_SAMPLES_STEP2_H

class step2 {
    public:
        void setup() {

            // Configure Serial Port for monitoring
            Serial.begin(115200);

            // Configure mode of LED port
            pinMode(LED_BUILTIN, OUTPUT);
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
#endif //IOT_SUPER_FRIDAY_SAMPLES_STEP2_H
