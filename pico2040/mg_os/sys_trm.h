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
  u8g2.drawXBMP(0, 0, trm_l_w, trm_l_h, trm_l);
  //gfx.print("trm", 0, 0);
}

void trmSys()
{
  gfx.print("Raspberry Pico 2040\nDual ARM Cortex-M0+\nCPU speed - 133 MHz\nFlash - 2 MB\nSRAM - 264 KB", 0, 10);
}

void functionB()
{

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
  headerTrm();
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