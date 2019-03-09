#include "SettingsService.h"
const int settingsAddr = 0; // EEPROM memory adderss
WeldSettings defaultSettings = {2, 35, 100, 90};
WeldSettings currentSettings = {0, 0, 0, 0};

SettingsService::SettingsService()
{
  EepromSettings = nullptr;
  WeldSettings getTmp;
  EEPROM.get(settingsAddr, getTmp);
  if(defaultSettings == getTmp)
  {
    defaultSettings = getTmp;
  }
  else
  {
    EEPROM.put(settingsAddr, defaultSettings); // put default if no settings found
  }

  currentSettings = defaultSettings;
  EepromSettings = &currentSettings;
}

void SettingsService::SaveSettings()
{
  if(defaultSettings != currentSettings)
  {
    EEPROM.put(settingsAddr, currentSettings);  
  }
}