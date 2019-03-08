#pragma once

#include "Arduino.h"
#include "SettingsService.h"
#include "SettingsModel.h"
#include <LiquidCrystal_I2C.h>

class DisplayService
{
  public:
    DisplayService();
            
    void OnPress(int value, LiquidCrystal_I2C lcd);
    void ConfigureButtons();
    void Begin(LiquidCrystal_I2C lcd);
    void SetCursor(int x, int y);
    void Print(String text);
    void Clear();

    ~DisplayService();

  private:
    void ButtonCenter(LiquidCrystal_I2C lcd);
    void ButtonLeft(LiquidCrystal_I2C lcd);
    void ButtonRight(LiquidCrystal_I2C lcd);
    void ButtonUp(LiquidCrystal_I2C lcd);
    void ButtonDown(LiquidCrystal_I2C lcd);
};
