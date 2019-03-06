#ifndef SettingsService_h
#define SettingsService_h
#include "Arduino.h"
#include <EEPROM.h>
#include "SettingsModel.h"

class SettingsService
{
  public:
    SettingsService();
    
    WeldSettings GetSettings();
    void SaveSettings(WeldSettings settings);
};

#endif
