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
void clearCommandTerminal();
void terminalCore(int state); void msgTimer(); void ttt();

Timer timer_1;
int textData{10};

/* command type */
struct Command
{
  char const *text;
  void (*f)();
  bool active;
};

/* data entered by the user */
String trmUserData = "";

/* user */
namespace user
{
  void userMenu()
  {
    gfx.print("User menu", 0, 20, 10, 6);
  }

  /* user-project to run */
  struct Project
  {
    const int number;
    void (*function)();
    const char *discription;
    bool active;
  };
}

/* systems */
namespace systems
{
  void systemsMenu()
  {
    gfx.print("Systems menu", 0, 20, 10, 6);
  }
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
      return 0; // go to User-project
      
      /*while (true)
      {
        terminalCore(0);
      }*/
    }
    else
    {
      while (textData > 0)
      {
        terminalCore(2);
        timer_1.timer(ttt, 1000);
        textData--;
      }
    }
    return 0;
  }

  /* terminal interface */
  void headerTerminal()
  {
    gfx.winkPrint(printf, "$" + trmUserData, 0, 10, 500);
  }
}

void ttt()
{

}

void msgTimer()
{
  gfx.print("Go to user menu after\nsecond ", 0, 10, 10, 6);
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
      u8g2.drawBox(sys.joi1x(), sys.joi1y(), 25, 25);
    }
    else
    {
      u8g2.drawFrame(sys.joi1x(), sys.joi1y(), 25, 25);
    }
  }
}

/* enumeration of objects - commands */
Command commands[]{
    {"symenu", systems::systemsMenu, false}, // 0
    {"usmenu", user::userMenu, false},       // 1
    {"hedtrm", mg::headerTerminal, false},   // 2
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
    {"clcbal", defGame::calculateMovementBall, false},
    {"msgtex", msgTimer, false}
};

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
  for (Command &command : commands)
  {
    if (command.active)
    {
      command.f();
    }
  }
}

/* pushing data onto the stack */
void terminalCore(int state) //run terminal user-any-systems / 1-user 0-systems
{
  if (not Serial.available())
  {
    if (state == 1) // go to User menu
    {
      commands[2].active = true; // header true
      commands[1].active = true; // user menu
      gfx.render(calcTerminal, 0);
    }
    else if (state == 0) //go to System menu
    {
      commands[0].active = true; // systems menu
      gfx.render(calcTerminal, 0);
    }
    else if (state == 2)
    {
      commands[14].active = true; // msg timer
      gfx.render(calcTerminal, 0);
    }
    //else return;
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
    else command.active = false;
  }
}
