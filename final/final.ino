/**************
   /******* switch *******/
/*
    5V : 5V
    GND : GND
    DATA : D4

   /******* switch *******/
/******* serrure *******/
/*
    5V : switch : Millieu
    GND : switch : Bas

   /******* serrure *******/
/******* capteur emprunt *******/
/*
    JAUNE : D2
    BLANC : D3
    5V : 5V
    GND : GND

   /******* capteur emprunt *******/
/******* leds *******/
/*
    5V : 5V
    GND : GND
    DATA : D8

   /******* leds *******/
/***************/
#include <Adafruit_Fingerprint.h>
#include <FastLED.h>

#if (defined(__AVR__) || defined(ESP8266)) && !defined(__AVR_ATmega2560__)

SoftwareSerial mySerial(2, 3);

#else

#define mySerial Serial1

#endif


Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);

#define RELAY 4

#define NUM_LEDS 2
#define DATA_PIN 8
#define CLOCK_PIN 13
CRGB leds[NUM_LEDS];

void setup() {
  Serial.begin(115200);
  pinMode(RELAY, OUTPUT);

  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);


  finger.begin(57600);
  delay(5);
  if (finger.verifyPassword())
  {
    Serial.println("Found fingerprint sensor!");
  } else
  {
    Serial.println("Did not find fingerprint sensor :(");
    while (1) {
      delay(1);
    }
  }

  finger.getTemplateCount();
}

void loop()
{
  fill_solid(leds, NUM_LEDS, CRGB::Black);
  FastLED.show();
  digitalWrite(RELAY, LOW);
  getFingerprintID();
  delay(50);

}

uint8_t getFingerprintID() {

  uint8_t p = finger.getImage();
  switch (p)
  {

    case FINGERPRINT_NOFINGER:

      Serial.print("-");
      return p;

  }



  p = finger.image2Tz();
  switch (p)
  {
    case FINGERPRINT_OK:

      Serial.println("-");
      break;

  }


  p = finger.fingerSearch();

  if (p == FINGERPRINT_OK)
  {
    Serial.println("acces ok");
    digitalWrite(RELAY, HIGH);

    for (int i = 0; i <= NUM_LEDS - 1; i++)
    {
      leds[i].setRGB( 0, 150, 0);
      FastLED.show();
    }

    delay(3000);
    return p;

  }

  else if (p == FINGERPRINT_NOTFOUND)
  {
    Serial.println("acces non");
    digitalWrite(RELAY, LOW);

    for (int i = 0; i <= NUM_LEDS - 1; i++)
    {
      leds[i].setRGB( 150, 0, 0);
      FastLED.show();
    }

    delay(3000);
    return p;
  }



  Serial.print("Found ID #"); Serial.print(finger.fingerID);
  Serial.print(" with confidence of "); Serial.println(finger.confidence);

  return finger.fingerID;
}
