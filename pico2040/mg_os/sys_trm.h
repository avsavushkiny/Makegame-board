/*
    terminal
*/

#pragma once
#include <Arduino.h>

class Terminal
{
  private:
  public:
} trm;

class InputOutput
{
  private:
  public:

  String getString(String oText)
  {
    if (Serial.available() > 0)
    {
      Serial.println(oText);
      return Serial.readString();
    }
    return "NULL";
  }

} io;

void terminalInputData()
{
  if (io.getString("Command: ") == "--")
  {
    if (io.getString("SYS") == "MCU")
    {
      Serial.println("RASPBERRY_PICO_2040_EN");
    }
    else if (io.getString("SYS") == "GFX")
    {
      Serial.println("ST7565_ERC12864_F_4W_SW_SPI");
    }
    else Serial.println("Non command");
  }
  else Serial.println("Non command");
}

void terminalGfx()
{

}