/*
    sys logo
*/

#pragma once
#include <Arduino.h>

#include "sys.h"
#include "sys_gfx.h"
#include "sys_xbmp.h"

/* prototype */
void frame_1(); void frame_2(); void frame_3();

/* main func */
void start_sys_logo()
{
  gfx.render(frame_1, 1500); // func, delay 1,5 sec
  gfx.render(frame_2, 3000);
  gfx.render(frame_3, 3000);
  gfx.clear();
}

/* func */
void frame_1()
{
  u8g2.drawXBMP(36, 18, mg_l_w, mg_l_h, mg_l);
}

void frame_2()
{
  gfx.print("Hey Bro!\nI am Console,\nOpen source project!", 6, 23);
}

void frame_3()
{
  gfx.print("Do you want to make\nyour own game?", 6, 23);
}