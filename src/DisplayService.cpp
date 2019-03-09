#include "DisplayService.h"
#include <LiquidCrystal_I2C.h>
#include "SettingsModel.h"


const int deviation = 5; // capturing button resistance with deviation

// Display text coordinates
const int settingsArrowColumn = 15; // Arrow text start column
const int settingsValueColumn = 9; // Setting value text column
int settingIndex = -1; // initial index of active display row

// Button resistance values
const int btnUp = 43;
const int btnDown = 63;
const int btnLeft = 18;
const int btnRight = 31;
const int btnCenter = 5;

void DisplayService::OnPress(int value)
{
  if(eepromSettings == nullptr)
  {
    return;
  }

  if(value > btnCenter - deviation && value < btnCenter + deviation)
  {
    ButtonCenter();
    return;
  }
  if(value > btnUp - deviation && value < btnUp + deviation)
  {
    ButtonUp();
    return;
  }
  if(value > btnDown - deviation && value < btnDown + deviation)
  {
    ButtonDown();
    return;
  }
  if(value > btnLeft - deviation && value < btnLeft + deviation)
  {
    ButtonLeft();
    return;
  }
  if(value > btnRight - deviation && value < btnRight + deviation)
  {
    ButtonRight();
    return;
  }
}

void DisplayService::LoadSettings(WeldSettings *settings)
{
  if(settings == nullptr)
  {
    return;
  }
  eepromSettings = settings;

   //Show menu
  
  LiquidCrystal_I2C::clear();
  LiquidCrystal_I2C::print("Count    ");
  LiquidCrystal_I2C::print(eepromSettings->pulseCount);
  
  LiquidCrystal_I2C::setCursor(0,1);
  LiquidCrystal_I2C::print("Duration ");
  LiquidCrystal_I2C::print(eepromSettings->pulseDuration);
  LiquidCrystal_I2C::print("ms");
  
  LiquidCrystal_I2C::setCursor(0,2);
  LiquidCrystal_I2C::print("Interval ");
  LiquidCrystal_I2C::print(eepromSettings->pulseInterval);
  LiquidCrystal_I2C::print("ms");
  
  LiquidCrystal_I2C::setCursor(0,3);
  LiquidCrystal_I2C::print("Power    ");
  LiquidCrystal_I2C::print(eepromSettings->pulsePower);
  LiquidCrystal_I2C::print("%");
}

void DisplayService::ButtonCenter()
{
  if(settingIndex < 0)
  {
    settingIndex = 0;
    LiquidCrystal_I2C::setCursor(settingsArrowColumn, settingIndex);
    LiquidCrystal_I2C::print("<<<<<");
  }
  else
  {
    LiquidCrystal_I2C::setCursor(settingsArrowColumn, settingIndex);
    LiquidCrystal_I2C::print("     ");
    settingIndex = -1;
  }
}

void DisplayService::ButtonUp()
{
  LiquidCrystal_I2C::setCursor(settingsArrowColumn, settingIndex);
  LiquidCrystal_I2C::print("     ");
  settingIndex < 1 ? settingIndex = 3 : settingIndex--;
  LiquidCrystal_I2C::setCursor(settingsArrowColumn, settingIndex);
  LiquidCrystal_I2C::print("<<<<<");
}

void DisplayService::ButtonDown()
{
  LiquidCrystal_I2C::setCursor(settingsArrowColumn, settingIndex);
  LiquidCrystal_I2C::print("     ");      
  settingIndex > 2 ? settingIndex = 0 : settingIndex++;
  LiquidCrystal_I2C::setCursor(settingsArrowColumn, settingIndex);
  LiquidCrystal_I2C::print("<<<<<");
}

void DisplayService::ButtonRight()
{
  if (settingIndex == 0)
  {
    eepromSettings->pulseCount > 4 ? eepromSettings->pulseCount = 0 : eepromSettings->pulseCount++;
    LiquidCrystal_I2C::setCursor(settingsValueColumn, settingIndex);
    LiquidCrystal_I2C::print("     ");      
    LiquidCrystal_I2C::setCursor(settingsValueColumn, settingIndex);
    LiquidCrystal_I2C::print(eepromSettings->pulseCount);
  }
  else if (settingIndex == 1)
  {
    eepromSettings->pulseDuration > 199 ? eepromSettings->pulseDuration = 20 : eepromSettings->pulseDuration++;
    LiquidCrystal_I2C::setCursor(settingsValueColumn, settingIndex);
    LiquidCrystal_I2C::print("     ");      
    LiquidCrystal_I2C::setCursor(settingsValueColumn, settingIndex);
    LiquidCrystal_I2C::print(eepromSettings->pulseDuration);
    LiquidCrystal_I2C::print("ms");
  }
  else if (settingIndex == 2)
  {
    eepromSettings->pulseInterval > 998 ? eepromSettings->pulseInterval = 20 : eepromSettings->pulseInterval++;
    LiquidCrystal_I2C::setCursor(settingsValueColumn, settingIndex);
    LiquidCrystal_I2C::print("     ");      
    LiquidCrystal_I2C::setCursor(settingsValueColumn, settingIndex);
    LiquidCrystal_I2C::print(eepromSettings->pulseInterval);
    LiquidCrystal_I2C::print("ms");
  }
  else if (settingIndex == 3)
  {
    eepromSettings->pulsePower > 99 ? eepromSettings->pulsePower = 0 : eepromSettings->pulsePower++;
    LiquidCrystal_I2C::setCursor(settingsValueColumn, settingIndex);
    LiquidCrystal_I2C::print("     ");      
    LiquidCrystal_I2C::setCursor(settingsValueColumn, settingIndex);
    LiquidCrystal_I2C::print(eepromSettings->pulsePower);
    LiquidCrystal_I2C::print("%");
  }
}

void DisplayService::ButtonLeft()
{
  if (settingIndex == 0)
  {
    eepromSettings->pulseCount < 1 ? eepromSettings->pulseCount = 5 : eepromSettings->pulseCount--;
    LiquidCrystal_I2C::setCursor(settingsValueColumn, settingIndex);
    LiquidCrystal_I2C::print("     ");      
    LiquidCrystal_I2C::setCursor(settingsValueColumn, settingIndex);
    LiquidCrystal_I2C::print(eepromSettings->pulseCount);
  }
  else if (settingIndex == 1)
  {
    eepromSettings->pulseDuration < 21 ? eepromSettings->pulseDuration = 200 : eepromSettings->pulseDuration--;
    LiquidCrystal_I2C::setCursor(settingsValueColumn, settingIndex);
    LiquidCrystal_I2C::print("     ");      
    LiquidCrystal_I2C::setCursor(settingsValueColumn, settingIndex);
    LiquidCrystal_I2C::print(eepromSettings->pulseDuration);
    LiquidCrystal_I2C::print("ms");
  }
  else if (settingIndex == 2)
  {
    eepromSettings->pulseInterval < 21 ? eepromSettings->pulseInterval = 999 : eepromSettings->pulseInterval--;
    LiquidCrystal_I2C::setCursor(settingsValueColumn, settingIndex);
    LiquidCrystal_I2C::print("     ");      
    LiquidCrystal_I2C::setCursor(settingsValueColumn, settingIndex);
    LiquidCrystal_I2C::print(eepromSettings->pulseInterval);
    LiquidCrystal_I2C::print("ms");
  }
  else if (settingIndex == 3)
  {
    eepromSettings->pulsePower < 1 ? eepromSettings->pulsePower = 100 : eepromSettings->pulsePower--;
    LiquidCrystal_I2C::setCursor(settingsValueColumn, settingIndex);
    LiquidCrystal_I2C::print("     ");      
    LiquidCrystal_I2C::setCursor(settingsValueColumn, settingIndex);
    LiquidCrystal_I2C::print(eepromSettings->pulsePower);
    LiquidCrystal_I2C::print("%");
  }
}

DisplayService::~DisplayService()
{
  
}
