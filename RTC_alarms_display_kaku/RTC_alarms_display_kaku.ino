#include <Wire.h>
#include <RTClib.h>  //Use Adafruit RTClib from library manager
#include <LiquidCrystal_I2C.h> //Use https://github.com/marcoschwartz/LiquidCrystal_I2C
#include <Time.h>
#include <TimeAlarms.h>
#include <RemoteTransmitter.h> //Use Fuzzylogic libraries

RTC_DS3231 rtc;
LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display

char daysOfTheWeek[7][12] = {"Zo", "Ma", "Di", "Wo", "Do", "Vr", "Za"};
// State of lights
bool Tuin = false;         // variable for Tuin verlichting

int sensorPin = A0;    // input pin for the lightmeter
int sensorValue = 0;  // variable to store the value coming from the sensor

// Intantiate a new KaKuTransmitter remote, use pin 11
KaKuTransmitter kaKuTransmitter(11);

void setup () {
  Serial.begin(115200);

  lcd.init(); // initialize the lcd 
  lcd.backlight(); // Backlight on
  lcd.setCursor(0,1);
  lcd.print("T:");         
  lcd.print(Tuin);
    
  if (! rtc.begin()) {
  //  Serial.println("Couldn't find RTC");
    lcd.setCursor(0,0);
    lcd.print("RTC not found");
    while (1);
  }

  if (rtc.lostPower()) {
    Serial.println("RTC lost power, lets set the time!");
    lcd.setCursor(0,0);
    lcd.print("RTC lost power");
    // following line sets the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // This line sets the RTC with an explicit date & time, for example to set
    // January 21, 2014 at 3am you would call:
    // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
    rtc.adjust(DateTime(2017, 4, 2, 15, 7, 0));
  }

  // create the alarms 
  Alarm.alarmRepeat(8,30,0, MorningAlarm);  // 8:30am every day
  Alarm.alarmRepeat(17,45,0,EveningAlarm);  // 5:45pm every day 
  Alarm.alarmRepeat(dowSaturday,8,30,30,WeeklyAlarm);  // 8:30:30 every Saturday 

 // Alarm.timerRepeat(15, Repeats);            // timer for every 15 seconds    
  Alarm.timerRepeat(15, TuinAAN);            // timer for every 15 seconds    
  Alarm.timerOnce(10, OnceOnly);             // called once after 10 seconds   
}

void loop () {
    DateTime now = rtc.now();

  lcd.setCursor(0,0);
  lcd.print(daysOfTheWeek[now.dayOfTheWeek()]);
  lcd.print(' ');
  lcd.print(now.day(), DEC);
  lcd.print('/');
  lcd.print(now.month(), DEC);
  lcd.print(' ');
  //lcd.print(now.year(), DEC);

 
  if(now.hour() < 10)  lcd.print('0');
  lcd.print(now.hour(), DEC);
  lcd.print(':');
  if(now.minute() < 10)  lcd.print('0');
  lcd.print(now.minute(), DEC);
  lcd.print(':');
  if(now.second() < 10)  lcd.print('0');
  lcd.print(now.second(), DEC);


  // read the value from the sensor:
  sensorValue = analogRead(sensorPin);
  lcd.setCursor(4,1);
  lcd.print("Licht:     ");
  lcd.setCursor(10,1);  
  lcd.print(sensorValue);
   
   Alarm.delay(1000);
}

// functions to be called when an alarm triggers:
void MorningAlarm(){
  lcd.print("Alarm: - turn lights off");    
}

void EveningAlarm(){
  lcd.print("Alarm: - turn lights on");           
}

void WeeklyAlarm(){
  lcd.print("Alarm: - its Monday Morning");      
}

void ExplicitAlarm(){
  lcd.print("Alarm: - this triggers only at the given date and time");       
}

void Repeats(){
  lcd.setCursor(0,1);
  lcd.print("15 seconds");         
  Serial.println("15 second timer");         
}

void OnceOnly(){
  Serial.println("This timer only triggers once");  
}

void TuinAAN(){
  if (Tuin == true) {
    Tuin = false;
    // Switch off KaKu-device 
    kaKuTransmitter.sendSignal('B',1,false);    
  } else if (sensorValue >900) {
    Tuin = true; 
    // Switch on KaKu-device 
    kaKuTransmitter.sendSignal('B',1,true);
  }
  lcd.setCursor(0,1);
  lcd.print("T:");         
  lcd.print(Tuin);  
}
