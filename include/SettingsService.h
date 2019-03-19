#pragma once

#include "Arduino.h"
#include "SettingsModel.h"

class SettingsService
{
  static WeldSettings defaultSettings;
  static WeldSettings currentSettings;
  static WeldSettings eepromSettings;

  public:
    SettingsService();
    
    WeldSettings *EepromSettings;
    static void SaveSettings();
    static void ResetToDefault();
    static void Clear();
};
