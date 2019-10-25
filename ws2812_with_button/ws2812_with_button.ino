/*
 * 
 * Alex 9-8-2019 started from debounce example and add fastled features from colorpallette
 * designed to fit digispark attiny85
 * 24-10-2019 added pallette choice
 * 
  Debounce

  Each time the input pin goes from LOW to HIGH (e.g. because of a push-button
  press), the output pin is toggled from LOW to HIGH or HIGH to LOW. There's a
  minimum delay between toggles to debounce the circuit (i.e. to ignore noise).

  The circuit:
  - LED attached from pin 1 to ground
  - pushbutton attached from pin 2 to internal pullup active to ground

  http://www.arduino.cc/en/Tutorial/Debounce
*/
#include <FastLED.h>

// constants won't change. They're used here to set pin numbers:
#define BTN_MNU     2      // the number of the menu button
#define BTN_UP      3      // the number of the up button
#define BTN_DN      4      // the number of the down button
#define LED_PIN     1      // the number of the onboard LED pin
#define DATA_PIN    0      // the pin connecting to the led strip
#define NUM_LEDS    2
#define UPDATES_PER_SECOND 20
#define BRIGHTNESS  128
#define LED_TYPE    WS2812
#define COLOR_ORDER GRB

CRGB leds[NUM_LEDS];
CRGBPalette16 currentPalette;
TBlendType    currentBlending;

// Variables will change:
int ledState = LOW;           // the current state of the output pin
int buttonState;              // the current reading from the input pin
int lastButtonState = LOW;    // the previous reading from the input pin
int mcount = 100;             //count number of button presses
int palettechoice = 1;        //palette chooser

// the following variables are unsigned longs because the time, measured in
// milliseconds, will quickly become a bigger number than can be stored in an int.
unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 50;    // the debounce time; increase if the output flickers


void setup() {
  pinMode(BTN_MNU, INPUT_PULLUP);
  pinMode(BTN_UP,  INPUT_PULLUP);
  pinMode(BTN_DN,  INPUT_PULLUP);
  pinMode(LED_PIN, OUTPUT);

  // set initial LED state
  digitalWrite(LED_PIN, ledState);

  FastLED.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS);
  FastLED.setBrightness(BRIGHTNESS);
  //currentPalette = PartyColors_p;// LavaColors_p; //HeatColors_p; //CloudColors_p; //ForestColors_p; //RainbowColors_p;
  currentBlending = LINEARBLEND;
}

void loop() {
  // read the state of the switch into a local variable:
  int reading = digitalRead(BTN_MNU);

  // check to see if you just pressed the button
  // (i.e. the input went from LOW to HIGH), and you've waited long enough
  // since the last press to ignore any noise:

  // If the switch changed, due to noise or pressing:
  if (reading != lastButtonState) {
    // reset the debouncing timer
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    // whatever the reading is at, it's been there for longer than the debounce
    // delay, so take it as the actual current state:

    // if the button state has changed:
    if (reading != buttonState) {
      buttonState = reading;

      // only toggle the LED if the new button state is LOW+
      if (buttonState == LOW) {
        ledState = !ledState;
        palettechoice += 1;
        //mcount = mcount + 20;
      }
    }
  }

  // set the onboard LED:
  digitalWrite(LED_PIN, ledState);

  
  lastButtonState = reading;// save the reading. Next time through the loop, it'll be the lastButtonState
  //leds[0] = CHSV(mcount,0,0); //update first led's color
  //leds[0] = CRGB::Red;
  //FastLED.show();
  //wsledtoggle ();
  
  ChangePalette();    //set currentPalette based on palettechoice
  
  static uint8_t startIndex = 0;
    startIndex +=  1; /* motion speed */
    
    FillLEDsFromPaletteColors( startIndex);
    
    FastLED.show();
    FastLED.delay(1000 / UPDATES_PER_SECOND);    
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


void FillLEDsFromPaletteColors( uint8_t colorIndex)
{
    uint8_t brightness = 125;
    
    for( int i = 0; i < NUM_LEDS; i++) {
        leds[i] = ColorFromPalette( currentPalette, colorIndex, brightness, currentBlending);
        colorIndex += 1;
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
