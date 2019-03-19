#include "SettingsService.h"
#include <EEPROM.h>

const int settingsAddr = 0; // EEPROM memory adderss
WeldSettings SettingsService::defaultSettings = {false, 2, 35, 100};
WeldSettings SettingsService::currentSettings;
WeldSettings SettingsService::eepromSettings;

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
  EepromSettings = nullptr;
  EEPROM.get(settingsAddr, eepromSettings);

  if(eepromSettings.isSaved)
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
