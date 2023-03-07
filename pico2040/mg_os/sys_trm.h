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

} io;

void terminalInputData()
{
  String data{};

  if (Serial.available() > 0)
  {
    data = Serial.readString(); data.trim();
    if (data == "--")
    {
      if (data == "sys")
      {
        Serial.println("RASPBERRY_PICO_2040_EN");
      }
    }
    else Serial.println("Non command");
  }
}

void terminalGfx()
{

}