#include "DisplayService.h"

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

SettingsService settingsService;
WeldSettings eepromSettings;

DisplayService::DisplayService()
{
  eepromSettings = settingsService.GetSettings();
}

void DisplayService::OnPress(int value, LiquidCrystal_I2C lcd)
{
  if(value > btnCenter - deviation && value < btnCenter + deviation)
  {
    ButtonCenter(lcd);
    return;
  }
  if(value > btnUp - deviation && value < btnUp + deviation)
  {
    ButtonUp(lcd);
    return;
  }
  if(value > btnDown - deviation && value < btnDown + deviation)
  {
    ButtonDown(lcd);
    return;
  }
  if(value > btnLeft - deviation && value < btnLeft + deviation)
  {
    ButtonLeft(lcd);
    return;
  }
  if(value > btnRight - deviation && value < btnRight + deviation)
  {
    ButtonRight(lcd);
    return;
  }
}

void DisplayService::Begin(LiquidCrystal_I2C lcd)
{
   //Show menu
  
  lcd.clear();
  lcd.print("Count    "); lcd.print(eepromSettings.pulseCount);
  
  lcd.setCursor(0,1);
  lcd.print("Duration "); lcd.print(eepromSettings.pulseDuration); lcd.print("ms");
  
  lcd.setCursor(0,2);
  lcd.print("Interval "); lcd.print(eepromSettings.pulseInterval); lcd.print("ms");
  
  lcd.setCursor(0,3);
  lcd.print("Power    "); lcd.print(eepromSettings.pulsePower); lcd.print("%");
}

void DisplayService::ButtonCenter(LiquidCrystal_I2C lcd)
{
  if(settingIndex < 0)
  {
    settingIndex = 0;
    lcd.setCursor(settingsArrowColumn, settingIndex);
    lcd.print("<<<<<");
  }
  else
  {
    lcd.setCursor(settingsArrowColumn, settingIndex);
    lcd.print("     ");
    settingIndex = -1;
  }
}

void DisplayService::ButtonUp(LiquidCrystal_I2C lcd)
{
  lcd.setCursor(settingsArrowColumn, settingIndex);
  lcd.print("     ");
  settingIndex < 1 ? settingIndex = 3 : settingIndex--;
  lcd.setCursor(settingsArrowColumn, settingIndex);
  lcd.print("<<<<<");
}

void DisplayService::ButtonDown(LiquidCrystal_I2C lcd)
{
  lcd.setCursor(settingsArrowColumn, settingIndex);
  lcd.print("     ");      
  settingIndex > 2 ? settingIndex = 0 : settingIndex++;
  lcd.setCursor(settingsArrowColumn, settingIndex);
  lcd.print("<<<<<");
}

void DisplayService::ButtonRight(LiquidCrystal_I2C lcd)
{
  if (settingIndex == 0)
  {
    eepromSettings.pulseCount > 4 ? eepromSettings.pulseCount = 0 : eepromSettings.pulseCount++;
    lcd.setCursor(settingsValueColumn, settingIndex);
    lcd.print("     ");      
    lcd.setCursor(settingsValueColumn, settingIndex);
    lcd.print(eepromSettings.pulseCount);
  }
  else if (settingIndex == 1)
  {
    eepromSettings.pulseDuration > 199 ? eepromSettings.pulseDuration = 20 : eepromSettings.pulseDuration++;
    lcd.setCursor(settingsValueColumn, settingIndex);
    lcd.print("     ");      
    lcd.setCursor(settingsValueColumn, settingIndex);
    lcd.print(eepromSettings.pulseDuration); lcd.print("ms");
  }
  else if (settingIndex == 2)
  {
    eepromSettings.pulseInterval > 998 ? eepromSettings.pulseInterval = 20 : eepromSettings.pulseInterval++;
    lcd.setCursor(settingsValueColumn, settingIndex);
    lcd.print("     ");      
    lcd.setCursor(settingsValueColumn, settingIndex);
    lcd.print(eepromSettings.pulseInterval); lcd.print("ms");
  }
  else if (settingIndex == 3)
  {
    eepromSettings.pulsePower > 99 ? eepromSettings.pulsePower = 0 : eepromSettings.pulsePower++;
    lcd.setCursor(settingsValueColumn, settingIndex);
    lcd.print("     ");      
    lcd.setCursor(settingsValueColumn, settingIndex);
    lcd.print(eepromSettings.pulsePower); lcd.print("%");
  }
}

void DisplayService::ButtonLeft(LiquidCrystal_I2C lcd)
{
  if (settingIndex == 0)
  {
    eepromSettings.pulseCount < 1 ? eepromSettings.pulseCount = 5 : eepromSettings.pulseCount--;
    lcd.setCursor(settingsValueColumn, settingIndex);
    lcd.print("     ");      
    lcd.setCursor(settingsValueColumn, settingIndex);
    lcd.print(eepromSettings.pulseCount);
  }
  else if (settingIndex == 1)
  {
    eepromSettings.pulseDuration < 21 ? eepromSettings.pulseDuration = 200 : eepromSettings.pulseDuration--;
    lcd.setCursor(settingsValueColumn, settingIndex);
    lcd.print("     ");      
    lcd.setCursor(settingsValueColumn, settingIndex);
    lcd.print(eepromSettings.pulseDuration); lcd.print("ms");
  }
  else if (settingIndex == 2)
  {
    eepromSettings.pulseInterval < 21 ? eepromSettings.pulseInterval = 999 : eepromSettings.pulseInterval--;
    lcd.setCursor(settingsValueColumn, settingIndex);
    lcd.print("     ");      
    lcd.setCursor(settingsValueColumn, settingIndex);
    lcd.print(eepromSettings.pulseInterval); lcd.print("ms");
  }
  else if (settingIndex == 3)
  {
    eepromSettings.pulsePower < 1 ? eepromSettings.pulsePower = 100 : eepromSettings.pulsePower--;
    lcd.setCursor(settingsValueColumn, settingIndex);
    lcd.print("     ");      
    lcd.setCursor(settingsValueColumn, settingIndex);
    lcd.print(eepromSettings.pulsePower); lcd.print("%");
  }
}

DisplayService::~DisplayService()
{
  
}
