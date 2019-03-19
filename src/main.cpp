#include <Arduino.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "DisplayService.h"

#define WELDBUTTONPIN 4   //Welding button pin
#define RELAYBUTTONPIN 11 //SSR pin
#define MENUBUTTONPIN A0 //Menu button

DisplayService displayService;
SettingsService settingsService;

bool isWelding = false;
bool isInterval = false;
unsigned long prevMillis = 0;
int curPulse = 0;

void setup()
{
  pinMode(WELDBUTTONPIN, INPUT_PULLUP); //read weld button
  pinMode(RELAYBUTTONPIN, OUTPUT);

  displayService.begin(20,4);

  //Load screen
  displayService.backlight();
  displayService.home();
  displayService.print("Evgeny's spot welder");
  displayService.setCursor(0,1);
  displayService.print("Loading");
  delay(700);  
  displayService.setCursor(0,1);
  displayService.print("Loading.");
  delay(700);
  displayService.setCursor(0,1);
  displayService.print("Loading..");
  delay(700);
  displayService.setCursor(0,1);
  displayService.print("Loading...");
  delay(700);

  displayService.LoadSettings(settingsService.EepromSettings);
}

void loop()
{
  int menuButton = analogRead(MENUBUTTONPIN);
  int weldButton = digitalRead(WELDBUTTONPIN);
  unsigned long curMillis = millis();

  if(weldButton == LOW && !isWelding)
  {
    isWelding = true;
    prevMillis = curMillis;
    curPulse = 0;
    isInterval = false;
  }

  if(isWelding)
  {
    if(curPulse < settingsService.EepromSettings->pulseCount)
    {
      int diff = curMillis - prevMillis;
      if(!isInterval)
      {
        digitalWrite(RELAYBUTTONPIN, HIGH);
        if(diff > settingsService.EepromSettings->pulseDuration)
        {
          Serial.println("Welding");
          digitalWrite(RELAYBUTTONPIN, LOW);
          curPulse++;
          isInterval = true;
        }
      } 
      else
      {
        if(diff > settingsService.EepromSettings->pulseDuration + settingsService.EepromSettings->pulseInterval)
        {
          isInterval = false;
          prevMillis = curMillis;
        }
      }
    }
    else if(weldButton == LOW)
    {
      isWelding = false;
    }
  }
  else
  {
    if(menuButton < 100)
    {
      delay(200);
      displayService.OnPress(menuButton);
    }
  }
}
