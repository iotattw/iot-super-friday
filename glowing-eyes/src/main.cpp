#include <Arduino.h>
#include <FastLED.h>

#define LED_PIN 18 /* This determines which pin to use */
#define NUM_LEDS 2 /* This determines the number of "eyes" */
#define DELAY 10   /* This determines the delay between setting colour values, bigger value = slower animation. */

CRGB leds[NUM_LEDS];
uint8_t brightness;

void setup()
{
    FastLED.addLeds<NEOPIXEL, LED_PIN>(leds, NUM_LEDS);
}

void loop()
{
    for (float t = 0.0; t < (2 * 3.14159); t += 0.01)
    {
        brightness = (128 * sin(t)) + 128;
        for (int x = 0; x < NUM_LEDS; x++)
        {
            leds[x] = CRGB::Red;
            leds[x].fadeLightBy(brightness);
            FastLED.show();
        }
        delay(DELAY);
    }
}
