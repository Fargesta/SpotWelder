#pragma once

#include "SettingsService.h"
#include "SettingsModel.h"
#include <LiquidCrystal_I2C.h>

enum MenuOptions
{
  None,
  Save,
  Clear,
  Reset
};

class DisplayService : public LiquidCrystal_I2C
{
  WeldSettings *eepromSettings;

  void ButtonCenter();
  void ButtonLeft();
  void ButtonRight();
  void ButtonUp();
  void ButtonDown();

  public:
    DisplayService() : LiquidCrystal_I2C (0x3F, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE) { eepromSettings = nullptr; }

    void OnPress(int value);
    void ConfigureButtons();
    void LoadSettings(WeldSettings *settings);
    ~DisplayService();
};
