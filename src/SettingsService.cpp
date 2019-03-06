#include "SettingsService.h"
const int settingsAddr = 0; // EEPROM memory adderss
WeldSettings eepromSettings = {5, 2, 35, 100, 90};

SettingsService::SettingsService()
{
  Settings getTmp;
  EEPROM.get(settingsAddr, getTmp);
  if(eepromSettings.eepromVersion == getTmp.eepromVersion)
  {
    eepromSettings = getTmp;
  }
  else
  {
    EEPROM.put(settingsAddr, eepromSettings); // put default if no settings found
  }

  SettingsService::GetSettings()
  {
    return eepromSettings;
  }

  void SaveSettings(Settings settings)
  {
    EEPROM.put(settingsAddr, settings);  
  }
}

bool operator==(const WeldSettings& lhs, const WeldSettings& rhs)
{
    return (lhs.pulseCount == rhs.pulseCount && 
            lhs.pulseDuration == rhs.pulseDuration &&
            lhs.pulseInterval == rhs.pulseInterval &&
            lhs.pulsePower == rhs.pulsePower);
}
