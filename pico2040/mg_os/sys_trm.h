/*
    terminal
*/

#pragma once
#include <Arduino.h>

#include "sys.h"
#include "sys_gfx.h"
#include "sys_xbmp.h"

class Terminal
{
private:
public:
} trm;

struct Command
{
  int nubmerCmd;
  bool stateCmd;
  String nameCmd;
  String infoCmd;
} cmd[] = 
{
{1, false, "sys", "Raspbery PICO 2040 gl ver"},
{2, false, "help", ""},
{3, false, "gfx", "ST7565_ERC12864_F_4W_SW_SPI"}
};

String textData{}, data{};

void calcTrm()
{
  if (Serial.available() != 0)
  {
    data = Serial.readString();
    for (int i = 0; i < 3; i++)
    {
      if (data == cmd[i].nameCmd)
      {
        textData = cmd[i].infoCmd;
      }
    }
  }
}

void ioTrm()
{
  u8g2.setFont(u8g2_font_6x10_tr);
  u8g2.setCursor(0, 10);
  u8g2.print(textData);
}

void terminal()
{
  calcTrm();
  gfx.render(ioTrm, 1500);
}











