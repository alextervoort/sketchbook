/*
 * 
 * Alex 9-8-2019 started from debounce example and add fastled features from colorpallette
 * designed to fit digispark attiny85
 * 24-10-2019 added pallette choice
 * 26-10-2019 switch to button library
 *
*/
#include <FastLED.h>
//#include <Button.h>
#include <JC_Button.h>          // https://github.com/JChristensen/JC_Button

// constants won't change. They're used here to set pin numbers:
Button BTN_MNU(2);          // the number of the menu button
Button BTN_UP(3);           // the number of the up button
Button BTN_DN(4);           // the number of the down button

const byte LED_PIN = 1;     // the number of the onboard LED pin
const byte DATA_PIN = 0;    // the pin connecting to the led strip
const byte NUM_LEDS = 2;    // number of conneced leds

#define LED_TYPE    WS2812
#define COLOR_ORDER GRB

CRGB leds[NUM_LEDS];
CRGBPalette16 currentPalette;
TBlendType    currentBlending;

// Variables will change:
bool menuenable = false;      // true if in menu
bool ledState = LOW;          // the initial state of the output pin
byte palettechoice = 1;       // palette chooser
byte brightness = 125;        // Initial brightness
byte updates_per_second = 20; // Update speed


void setup() {
  BTN_MNU.begin();
  BTN_UP.begin();
  BTN_DN.begin();

  pinMode(LED_PIN, OUTPUT);          // set onboard LED as output
  digitalWrite(LED_PIN, ledState);   // set initial onboard LED state

  FastLED.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS);
  FastLED.setBrightness(brightness);
  currentPalette = PartyColors_p;// LavaColors_p; //HeatColors_p; //CloudColors_p; //ForestColors_p; //RainbowColors_p;
  currentBlending = LINEARBLEND;
}

void loop() {
  BTN_MNU.read(); 
  if (BTN_MNU.wasReleased()) {
    menuenable = true;
    Menu();
    }

  
  if (BTN_DN.wasReleased()) { 
    ChangeBrightness(); 
    }
  
  
  static byte startIndex = 0;
  startIndex +=  1; /* motion speed */
    
  FillLEDsFromPaletteColors( startIndex);
  FastLED.show();
  FastLED.delay(1000 / updates_per_second);    
}


void wsledtoggle ()
{
  if (ledState == HIGH) {
    leds[0] = CRGB::Yellow;
  }
  else {
    leds[0] = CRGB::Black;
  }
  FastLED.show();
}


void FillLEDsFromPaletteColors( byte colorIndex)
{  
  for( int i = 0; i < NUM_LEDS; i++) {
    leds[i] = ColorFromPalette( currentPalette, colorIndex, brightness, currentBlending);
    colorIndex += 10;
    }
}

void ChangePalette()
{
  if( palettechoice == 1)  { currentPalette = RainbowColors_p;     currentBlending = LINEARBLEND; }
  if( palettechoice == 2)  { currentPalette = PartyColors_p;       currentBlending = LINEARBLEND; }
  if( palettechoice == 3)  { currentPalette = LavaColors_p;        currentBlending = LINEARBLEND; }
  if( palettechoice == 4)  { currentPalette = HeatColors_p;        currentBlending = LINEARBLEND; }
  if( palettechoice == 5)  { currentPalette = CloudColors_p;       currentBlending = LINEARBLEND; }
  if( palettechoice == 6)  { currentPalette = ForestColors_p;      currentBlending = LINEARBLEND; }
  if( palettechoice == 7)  { currentPalette = RainbowColors_p;     currentBlending = LINEARBLEND; 
                             palettechoice = 1;}
}

void ChangeBrightness()
{
  if( brightness < 205) {
    brightness += 50;
  }
  else {
    brightness = 0;
  }
  FastLED.setBrightness(brightness);
}

void Menu()
{
  ledState = HIGH;       //  LED on in menu
  digitalWrite(LED_PIN, ledState);

  while ( menuenable ){  // stay in menu untill menu button is pressed again
  BTN_MNU.read(); 
    if (BTN_MNU.wasReleased()) {
      menuenable = false;
      ledState = LOW;       //  LED off out of menu
      digitalWrite(LED_PIN, ledState);
      //return;
      }
    
  BTN_UP.read(); 
    if (BTN_UP.wasReleased()) {
      palettechoice += 1; // next palette
      ChangePalette();    // set currentPalette based on palettechoice
      } 
  } 
}
