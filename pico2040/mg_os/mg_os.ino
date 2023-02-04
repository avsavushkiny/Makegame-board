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

/* user include */


/* run */
void setup()
{
  gfx.screen();
  analogReadResolution(12);
}

void loop()
{
  start_sys_logo();
}
