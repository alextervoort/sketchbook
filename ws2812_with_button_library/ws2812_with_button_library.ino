/*
 * 
 * Alex 9-8-2019 started from debounce example and add fastled features from colorpallette
 * designed to fit digispark attiny85
 * 24-10-2019 added pallette choice
 * 26-10-2019 switch to button library
 *
*/
#include <FastLED.h>
#include <JC_Button.h>          // https://github.com/JChristensen/JC_Button

// constants won't change. They're used here to set pin numbers:
Button BTN_MNU(5);          // the number of the menu button
Button BTN_UP(3);           // the number of the up button
Button BTN_DN(2);           // the number of the down button

//const byte LED_PIN = 1;     // the number of the onboard LED pin
const byte DATA_PIN = 0;    // the pin connecting to the led strip
const byte NUM_LEDS = 3;    // number of conneced leds

#define LED_TYPE    WS2812
#define COLOR_ORDER GRB

CRGB leds[NUM_LEDS];
CRGBPalette16 currentPalette;
TBlendType    currentBlending;

// Variables will change:
bool menuenable = false;      // true if in menu
//bool ledState = LOW;          // the initial state of the output pin
byte palettechoice = 1;       // palette chooser
byte brightness = 105;        // Initial brightness
byte updates_per_second = 50; // Update speed


void setup() {
  BTN_MNU.begin();
  BTN_UP.begin();
  BTN_DN.begin();

  //pinMode(LED_PIN, OUTPUT);          // set onboard LED as output
  //digitalWrite(LED_PIN, ledState);   // set initial onboard LED state

  FastLED.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS);
  FastLED.setBrightness(brightness);
  currentPalette = ForestColors_p;//PartyColors_p;// LavaColors_p; //HeatColors_p; //CloudColors_p; //ForestColors_p; //RainbowColors_p;
  currentBlending = LINEARBLEND;
}

void loop() {
  BTN_MNU.read();                   //Check if memu button is pressed, if so enter menu
  if (BTN_MNU.wasPressed()) { menuenable = true; Menu(); }

  static byte startIndex = 0;
  startIndex +=  1; /* motion speed */
    
  FillLEDsFromPaletteColors(startIndex);
  FastLED.show();
  FastLED.delay(1000 / updates_per_second);    
}

void Menu()
{
  byte menulevel = 1;           // Keep track of menu depth
  FastLED.clear();              // Start with all led's off

  while ( menuenable ){         // stay in menu untill all menu levels are used
    if (menulevel > 3) {menuenable = false; }
    if (menulevel == 1) {leds[0] = CRGB::Red; }
    if (menulevel == 2) {leds[0] = CRGB::Blue; }
    if (menulevel == 3) {leds[0] = CRGB::Green; }
    
    BTN_MNU.read(); 
      if (BTN_MNU.wasPressed()) { menulevel++; }
    
    BTN_UP.read(); 
      if (BTN_UP.wasPressed()) {
        if (menulevel == 1) {palettechoice++; // next palette
          ChangePalette();    // set currentPalette based on palettechoice
          }
        if (menulevel == 2) { ChangeSpeed(true); }    // Faster
        if (menulevel == 3) { ChangeBrightness(true); }      // Brighter
      }
  
    BTN_DN.read(); 
    if (BTN_DN.wasPressed()) {
      if (menulevel == 1) {palettechoice--; // previous palette
          ChangePalette();    // set currentPalette based on palettechoice
        }
      if (menulevel == 2) { ChangeSpeed(false); }      // Slower
      if (menulevel == 3) { ChangeBrightness(false); }       // Dimmer
      }
  
    // show changes
    for( int i = 1; i < NUM_LEDS; i++) {
      leds[i] = ColorFromPalette( currentPalette, 127, brightness, currentBlending);
    }
    FastLED.show();
    }
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
                             palettechoice = 0;}
}

void ChangeBrightness(bool up)    // Brightness up if true, down otherwise. Keep levels between 25 and 250
{
  if( brightness < 225 && up ) { brightness += 25; }
  if( brightness > 50 && !up ) { brightness -= 25; }
  FastLED.setBrightness(brightness);
} 

void ChangeSpeed(bool faster)   // Increase update speed if true, slow otherwise. Keep speed between ?
{
  if( updates_per_second > 15 && faster ) { updates_per_second -= 10; }
  if( updates_per_second < 200 && !faster ) { updates_per_second += 10; }
}
