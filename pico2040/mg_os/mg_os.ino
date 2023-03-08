/*
█▄─▀█▀─▄█─▄▄▄▄█─▄▄─█─▄▄▄▄█
██─█▄█─██─██▄─█─██─█▄▄▄▄─█
▀▄▄▄▀▄▄▄▀▄▄▄▄▄▀▄▄▄▄▀▄▄▄▄▄▀

makegame OS / beta 1 / 19/12/22
*/

#include <Arduino.h>

/* sys include */
#include "sys.h"          //sticks
#include "sys_gfx.h"      //lcd
#include "sys_xbmp.h"     //bitmap
#include "sys_page_0.h"   //user start page
#include "sys_logo.h"     //start page - logotype
#include "sys_exc.h"      //exceptions
#include "sys_trm.h"      //terminal

/* user include */

/* global variable */

/* run */
void setup()
{
  gfx.screen();
  analogReadResolution(12);
  start_sys_logo();

  stateOs = SYS_OK;
}

void loop()
{
  terminal();
}