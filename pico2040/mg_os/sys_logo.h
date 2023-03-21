/*
  sys logo
*/

#pragma once

#include "sys.h"
#include "sys_gfx.h"
#include "sys_xbmp.h"

/* prototype */
void frame_1(); void frame_2(); void frame_3(); void frame_4();

/* main func */
void systemsLogo()
{
  gfx.render(frame_1, 2000); // func, delay 2 sec
  gfx.render(frame_2, 1500);
  gfx.render(frame_3, 1500);
  gfx.render(frame_4, 1500);
  gfx.clear();
}

/* func */
void frame_1()
{
  u8g2.drawXBMP(36, 18, mg_l_w, mg_l_h, mg_l);
}

void frame_2()
{
  gfx.print("Hey Bro!\nI am Console,\nOpen source project!", 6, 23, 10, 6);
}

void frame_3()
{
  gfx.print("Do you want to make\nyour own game?", 6, 23, 10, 6);
}

void frame_4()
{
  gfx.print("Enjoy!", 6, 23, 10, 6);
}