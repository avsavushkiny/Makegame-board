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

class Terminal
{
  private:
  public:

} trm;

String userData = "command";

void headerTrm()
{
  //u8g2.drawXBMP(0, 2, trm_l_w, trm_l_h, trm_l);
  gfx.winkPrint(printf, "<" + userData + ">", 0, 9, 300);
  //u8g2.drawHLine(0, 11, 128);
  //gfx.print("" + userData + "", 18, 10);
}

void trmSys()
{
  gfx.print("Raspberry Pico 2040\nDual ARM Cortex-M0+\nCPU speed - 133 MHz\nFlash - 2 MB\nSRAM - 264 KB", 0, 20);
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
  //gfx.drawCursor(true);

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
  Serial.readBytesUntil('\n', text, sizeof(text)); userData = text;
  for (Command &command : commands)
  {
    if (not strncmp(command.text, text, 3))
    {
      command.active = true;
    }
  }
}