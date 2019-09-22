//Werkt ook in digispark

#include "FastLED.h"
//FASTLED_USING_NAMESPACE

#define DATA_PIN    0
#define LED_TYPE    WS2812B
#define COLOR_ORDER GRB
#define NUM_LEDS    5
CRGB leds[NUM_LEDS];

#define BRIGHTNESS         50  // 0-255
#define FRAMES_PER_SECOND  60

uint8_t gHue = 0; // rotating "base color" used by many of the patterns

void setup() {
   // tell FastLED about the LED strip configuration
  FastLED.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS);
  FastLED.setBrightness(BRIGHTNESS); // Adds just four bytes
  
}

void loop() { 
  rainbowWithGlitter ();

  // send the 'leds' array out to the actual LED strip
  FastLED.show();
  // insert a delay to keep the framerate modest
  delay(1000 / FRAMES_PER_SECOND);

  // do some periodic updates
  EVERY_N_MILLISECONDS( 20 ) {
    gHue++;  // slowly cycle the "base color" through the rainbow
  }
}

void rainbow() {
  // FastLED's built-in rainbow generator
  fill_rainbow( leds, NUM_LEDS, gHue, 7);
}

void rainbowWithGlitter() {
  // built-in FastLED rainbow, plus some random sparkly glitter
  rainbow();
  addGlitter(30);
}

void addWhiteGlitter( fract8 chanceOfGlitter) {
  if ( random8() < chanceOfGlitter) {
    leds[ random16(NUM_LEDS) ] += CRGB::White;
  }

}

void addGlitter( fract8 chanceOfGlitter) {
  byte i= random8();
  if ( i < chanceOfGlitter/3 ){
    leds[ random16(NUM_LEDS) ] += CRGB::White;
  }
  else if ( i >= chanceOfGlitter/3 && i < 2*chanceOfGlitter/3 ){
    leds[ random16(NUM_LEDS) ] += CRGB::Green;
  }
  else if ( i >= 2*chanceOfGlitter/3 && i < chanceOfGlitter){
    leds[ random16(NUM_LEDS) ] += CRGB::Red;
  }
}

void onlyGlitter() {
  fadeToBlackBy( leds, NUM_LEDS, 500);
  addGlitter(40);
}
