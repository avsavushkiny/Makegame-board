/*
  terminal
*/

#pragma once

#include "sys.h"
#include "mg.h"
#include "sys_gfx.h"
#include "sys_xbmp.h"
#include "sys_logo.h"
#include "sys_def_game.h"

/* prototype */
void clearCommandTerminal(); void calcUserMenu(); void terminalCore(bool state);

/* command type */
struct Command
{
  char const *text;
  void (*f)();
  bool active;
};

/* data entered by the user */
String trmUserData = "enter the command";

/* terminal interface */
void headerTerminal()
{
  gfx.winkPrint(printf, "$" + trmUserData, 0, 10, 500);
}

/* user */
namespace user
{
  void calcUserMenu()
  {

  }
  
  void userMenu()
  {
    while (true)
    {
      
    }
  }

  /* user-object to run */
  struct Project
  {
    const int number;
    void (*function)();
    const char *discription;
    bool active;
  };
}

namespace mg
{
  /* initial settings */
  int initialization()
  {
    gfx.screen();
    analogReadResolution(12);
    return 0;
  }

  /* start greeting */
  int greetings()
  {
    systemsLogo();
    return 0;
  }

  /* start command-line-interface terminal */
  int terminal()
  {
    if (sys.sw0() == true)
    {
      while (true)
      {
        terminalCore(true);
      }
    }
    else
    {
      while (true)
      {
        terminalCore(false);
      }
    }

    return 0;
  }
}

/* standard commands */
namespace defCommand
{
  /* microcontroller information */
  void infoSystems()
  {
    gfx.print("Raspberry Pico 2040\nDual ARM Cortex-M0+\nCPU speed - 133 MHz\nFlash - 2 MB\nSRAM - 264 KB", 0, 20, 10, 6);
  }

  /* graphics chip information */
  void infoGfx()
  {
    gfx.print("Chip - ST7565\nRes - 128x64\nVersion - White", 0, 20, 10, 6);
  }

  /* information about the analog-to-digital converter */
  void infoAdc()
  {
    if (sys.sw0() == true)
    {
      u8g2.drawBox(sys.joi0x(), sys.joi0y(), 10, 10);
    }
    else
    {
      u8g2.drawFrame(sys.joi0x(), sys.joi0y(), 10, 10);
    }

    if (sys.sw1() == true)
    {
      u8g2.drawBox(sys.joi0x(), sys.joi1y(), 25, 25);
    }
    else
    {
      u8g2.drawFrame(sys.joi0x(), sys.joi1y(), 25, 25);
    }
  }
}

/* enumeration of objects - commands */
Command commands[]{
    {"usmenu", user::userMenu, false},
    {"system", defCommand::infoSystems, false},
    {"graphc", defCommand::infoGfx, false},
    {"sticks", defCommand::infoAdc, false},
    {"clrcom", clearCommandTerminal, false},
    {"drwfld", defGame::drawField, false},
    {"drwrac", defGame::drawRacket, false},
    {"drwbal", defGame::drawBall, false},
    {"drwscr", defGame::drawScore, false},
    {"drwlog", defGame::drawLogo, false},
    {"clcrac", defGame::calculateMovementRackets, false},
    {"clcbal", defGame::calculateMovementBall, false}};

/* delete all commands */
void clearCommandTerminal()
{
  for (Command &command : commands)
  {
    command.active = false;
  }
}

/* command stack */
void calcTerminal()
{
  headerTerminal();

  for (Command &command : commands)
  {
    if (command.active)
    {
      command.f();
    }
  }
}

void calcTerminalNoHeader()
{
  for (Command &command : commands)
  {
    if (command.active)
    {
      command.f();
    }
  }
}

/* pushing data onto the stack */
void terminalCore(bool state)
{
  if (state == true)
  {
    gfx.render(calcTerminal, 0);

    if (not Serial.available())
    {
      return;
    }

    char text[10]{};
    Serial.readBytesUntil('\n', text, sizeof(text));
    trmUserData = text;

    for (Command &command : commands)
    {
      if (not strncmp(command.text, text, 6))
      {
        command.active = true;
      }
      // else
      // command.active = false;
    }
  }
  else
  {
    gfx.render(calcTerminalNoHeader, 0);
    commands[0].active = true;
  }
}
