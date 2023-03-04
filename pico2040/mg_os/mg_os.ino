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


/* global variable */
enum STATE_OS
{
  OK,
  ERROR,
} stateOs;

/* func */
void messageOs()
{
  u8g2.setFont(u8g2_font_6x10_tr);

  String title_1 = "Error. No procces";

  if (stateOs == ERROR)
  {
  u8g2.setCursor(6, 20);
  u8g2.print(title_1); 
  }
}

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
    gfx.render(messageOs, 5000);
  }
}