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
  gfx.render(frame_3, 30500);
  gfx.clear();
}

/* func */
void frame_1()
{
  u8g2.drawXBMP(36, 18, mg_l_w, mg_l_h, mg_l);
}

void frame_2()
{
  u8g2.setFont(u8g2_font_6x10_tr);

  String title_1 = "Hey Bro!";
  String title_2 = "I am Console";  
  String title_3 = "Do you want to make";
  String title_4 = "your own game?";

  u8g2.setCursor(6, 20);
  u8g2.print(title_1);

  u8g2.setCursor(6, 30);
  u8g2.print(title_2);

  u8g2.setCursor(6, 38);
  u8g2.print(title_3);

  u8g2.setCursor(6, 46);
  u8g2.print(title_4);
}

char text[] = "Hey Bro!\nI am Console,\nOpen source project!";

void frame_3()
{
  int sizeText = sizeof(text); int y{10};
  
  for(int i = 0, x = 0; i < sizeText, x < (sizeText*6); i++, x+=6)
  {
    u8g2.setFont(u8g2_font_6x10_tr);
    u8g2.setCursor(x, y);
    u8g2.print(text[i]);

    if (text[i] == '\n') 
    {
      y += 10; x = -6;
    }
  }

  Serial.println(sizeText);
}



