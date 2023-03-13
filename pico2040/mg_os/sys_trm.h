/*
  terminal
*/

#pragma once

#include <Arduino.h>

#include "sys.h"
#include "sys_gfx.h"
#include "sys_xbmp.h"
#include "sys_logo.h"

struct Command
{
  char const *text;
  void (*f)();
  bool active;
};

String trmUserData = "command";

void headerTerminal()
{
  //u8g2.drawXBMP(0, 2, trm_l_w, trm_l_h, trm_l);
  gfx.winkPrint(printf, "trm " + trmUserData , 0, 9, 300);
  u8g2.drawHLine(0, 11, 128);
}

/* info */
void infoSystems()
{
  gfx.print("Raspberry Pico 2040\nDual ARM Cortex-M0+\nCPU speed - 133 MHz\nFlash - 2 MB\nSRAM - 264 KB", 0, 20);
}

void infoGfx()
{
  gfx.print("Chip - ST7565\nRes - 128x64\nVersion - White", 0, 20);
}

/* all commands */
Command commands[]
{
  { "sys", infoSystems, false },
  { "gfx", infoGfx, false },
};

/* terminal core */
void calcTerminal()
{
  headerTerminal();

  for (Command const &command : commands)
  {
    if (command.active)
    {
      command.f();
    }
  }
}

/* entry point */
void terminal() 
{
  gfx.render(calcTerminal, 0);
  
  if (not Serial.available()) {
    return;
  }

  char text[10]{};
  Serial.readBytesUntil('\n', text, sizeof(text));
  trmUserData = text;

  for (Command &command : commands)
  {
    if (not strncmp(command.text, text, 3))
    {
      command.active = true;
    }
    else command.active = false;
  }
}





