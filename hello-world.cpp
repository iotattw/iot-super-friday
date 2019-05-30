/* Hello World */
#include "Arduino.h"

#define LED_BUILTIN 2

void setup()
{
    // open up a serial port at 9600 baud
    Serial.begin(9600);
    // initialize LED digital pin as an output
    pinMode(LED_BUILTIN, OUTPUT);
}

void loop()
{
    // turn the LED on (HIGH is the voltage level)
    digitalWrite(LED_BUILTIN, HIGH);
    Serial.println("Turned LED on");

    // wait for a second
    delay(1000);

    // turn the LED off by making the voltage LOW
    digitalWrite(LED_BUILTIN, LOW);
    Serial.println("Turned LED off");

    // wait for a second
    delay(1000);
}