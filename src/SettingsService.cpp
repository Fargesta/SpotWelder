#include "SettingsService.h"
const int settingsAddr = 0; // EEPROM memory adderss

bool operator==(const WeldSettings &lhs, const WeldSettings &rhs)
{
    return (lhs.pulseCount == rhs.pulseCount && 
            lhs.pulseDuration == rhs.pulseDuration &&
            lhs.pulseInterval == rhs.pulseInterval &&
            lhs.isSaved == rhs.isSaved);
}

bool operator!=(const WeldSettings &lhs, const WeldSettings &rhs)
{
    return (lhs.pulseCount != rhs.pulseCount ||
            lhs.pulseDuration != rhs.pulseDuration ||
            lhs.pulseInterval != rhs.pulseInterval ||
            lhs.isSaved == rhs.isSaved);
}

SettingsService::SettingsService()
{
  defaultSettings = {false, 2, 35, 100};
  EepromSettings = nullptr;
  WeldSettings getTmp;
  EEPROM.get(settingsAddr, eepromSettings);

  if(getTmp.isSaved)
  {
    defaultSettings = eepromSettings;
  }

  currentSettings = defaultSettings;
  EepromSettings = &currentSettings;
}

void SettingsService::SaveSettings()
{
  if(defaultSettings != currentSettings)
  {
    currentSettings.isSaved = true;
    EEPROM.put(settingsAddr, currentSettings);  
  }
}

void SettingsService::Clear()
{
  currentSettings = eepromSettings;
}

void SettingsService::ResetToDefault()
{
  currentSettings = defaultSettings;
}
