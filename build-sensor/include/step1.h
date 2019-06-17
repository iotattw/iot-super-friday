//
// Created by Timothy Findlay on 2019-06-17.
//

#ifndef IOT_SUPER_FRIDAY_SAMPLES_STEP1_H
#define IOT_SUPER_FRIDAY_SAMPLES_STEP1_H

class step1 {
    public:
        void setup() {
            // Configure mode of LED port
            pinMode(LED_BUILTIN, OUTPUT);
        }

        void loop() {
            digitalWrite(LED_BUILTIN, HIGH);
            delay(1000);
            digitalWrite(LED_BUILTIN, LOW);
            delay(1000);
        }

};

#endif //IOT_SUPER_FRIDAY_SAMPLES_STEP1_H
