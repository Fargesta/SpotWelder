#pragma once

#include "Arduino.h"
#include <EEPROM.h>
#include "SettingsModel.h"

class SettingsService
{
  public:
    SettingsService();
    
    WeldSettings *EepromSettings;
    void SaveSettings();
};
