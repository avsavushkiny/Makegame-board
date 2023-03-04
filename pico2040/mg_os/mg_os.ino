/*
    makegame OS / beta 1
    19/12/22
*/
#include <Arduino.h>

/* sys include */
#include "sys.h"
#include "sys_gfx.h"
#include "sys_xbmp.h"
#include "sys_page_0.h"
#include "sys_logo.h"
#include "sys_exc.h"

/* user include */

/* global variable */

/* run */
void setup()
{
  gfx.screen();
  analogReadResolution(12);
  start_sys_logo();

  stateOs = OK;
}

void loop()
{
  if (stateOs == OK)
  {
    delay(5000); stateOs = ERROR;
  }
  
  else if(stateOs == ERROR)
  {
    gfx.render(messageOs, 0);
  }
}