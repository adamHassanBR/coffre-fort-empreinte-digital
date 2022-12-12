#include <FastLED.h>


#define NUM_LEDS 8


#define DATA_PIN 8
#define CLOCK_PIN 13

CRGB leds[NUM_LEDS];

void setup() 
{ 

    FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);

}

void loop() 
{ 
  fill_solid(leds, NUM_LEDS, CRGB::Black);

  for(int i = 0; i <= NUM_LEDS-1; i++)
  {
    leds[i] = CRGB::#fff;
    FastLED.show();
    delay(500);
  }
  delay(1000);

}
