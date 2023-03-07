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
  char nameCmd[20];
} cmd[]

{1, false, "sys"},
{2, false, "help"}
;

void terminal()
{
}