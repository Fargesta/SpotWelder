#include "SettingsService.h"
const int settingsAddr = 0; // EEPROM memory adderss
WeldSettings eepromSettings = {2, 35, 100, 90};

SettingsService::SettingsService()
{
  WeldSettings getTmp;
  EEPROM.get(settingsAddr, getTmp);
  if(eepromSettings == getTmp)
  {
    eepromSettings = getTmp;
  }
  else
  {
    EEPROM.put(settingsAddr, eepromSettings); // put default if no settings found
  }
}

WeldSettings SettingsService::GetSettings()
{
  return eepromSettings;
}

void SettingsService::SaveSettings(WeldSettings settings)
{
  if(settings != eepromSettings)
  {
  EEPROM.put(settingsAddr, settings);  
  }
}