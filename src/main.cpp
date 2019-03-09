#include <Wire.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "DisplayService.h"

#define DETECT 2          //zero cross detect
#define GATE 3            //TRIAC gate
#define PULSE 2           //trigger pulse width (counts)
#define WELDBUTTONPIN 4   //Welding button pin
#define RELAYBUTTONPIN 11 //SSR pin

DisplayService displayService;
SettingsService settingsService;
bool isWelding = false;
bool isInterval = false;
unsigned long prevMillis = 0;
int curPulse = 0;

//Interrupt Service Routines
void zeroCrossingInterrupt()
{ //zero cross detect   
  TCCR1B=0x04; //start timer with divide by 256 input
  TCNT1 = 0;   //reset timer - count from zero
}

ISR(TIMER1_COMPA_vect)
{                           //comparator match
  digitalWrite(GATE,HIGH);  //set TRIAC gate to high
  TCNT1 = 65536-PULSE;      //trigger pulse width
}

ISR(TIMER1_OVF_vect)
{                         //timer1 overflow
  digitalWrite(GATE,LOW); //turn off TRIAC gate
  TCCR1B = 0x00;          //disable timer stopd unintended triggers
}

void setup()
{
  pinMode(DETECT, INPUT);     //zero cross detect
  digitalWrite(DETECT, HIGH); //enable pull-up resistor
  pinMode(GATE, OUTPUT);      //TRIAC gate control
  pinMode(WELDBUTTONPIN, INPUT_PULLUP); //read weld button
  pinMode(RELAYBUTTONPIN, OUTPUT);

  // set up Timer1 
  //(see ATMEGA 328 data sheet pg 134 for more details)
  OCR1A = 100;      //initialize the comparator
  TIMSK1 = 0x03;    //enable comparator A and overflow interrupts
  TCCR1A = 0x00;    //timer control registers set for
  TCCR1B = 0x00;    //normal operation, timer disabled

  // set up zero crossing interrupt
  attachInterrupt(0, zeroCrossingInterrupt, RISING);    
  //IRQ0 is pin 2. Call zeroCrossingInterrupt 
  //on rising signal

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
  OCR1A = 625 * settingsService.EepromSettings->pulsePower / 100;
  int menuButton = analogRead(A0);
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
