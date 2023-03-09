/*
    terminal
*/

#pragma once

#include <Arduino.h>

#include "sys.h"
#include "sys_gfx.h"
#include "sys_xbmp.h"
#include "sys_logo.h"

int k{10};

struct Command
{
  char const *text;
  void (*f)();
  bool active;
};

void headerTrm()
{
  u8g2.setFont(u8g2_font_6x10_tr);
  u8g2.setCursor(0, 10);
  u8g2.print("trm");
}

void trmSys()
{
  u8g2.setFont(u8g2_font_6x10_tr);
  u8g2.setCursor(0, 10);
  u8g2.print("Raspberry Pico 2040 \n Dual ARM Cortex-M0+ \n Raspberry Pi co ltd");
  Serial.println();
}

void functionB()
{
  u8g2.setFont(u8g2_font_6x10_tr);
  u8g2.setCursor(0, 20);
  u8g2.print("function B");
  Serial.println("This is function B.");
}

void functionC()
{
  u8g2.drawXBMP(36, 18, mg_l_w, mg_l_h, mg_l);
}

//drawField
//drawBall
//drawRackets
//drawTable
//calculate

Command commands[]
{
  { "sys", trmSys, false },
  { "gfx", functionB, false },
  { "mgl", functionC, false }
};

void bodyTrm()
{
  for (Command const &command : commands)
  {
    if (command.active)
    {
      command.f();
    }
  }
}

void terminal() 
{
  gfx.render(bodyTrm, 0);
  
  if (not Serial.available()) {
    return;
  }

  char text[10]{};
  Serial.readBytesUntil('\n', text, sizeof(text));
  for (Command &command : commands)
  {
    if (not strncmp(command.text, text, 3))
    {
      command.active = true;
    }
  }
}