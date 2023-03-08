/*
    graphics output library
    ST7565 128*64  

    reference manual https://github.com/olikraus/u8g2/wiki/u8g2reference
    fonts            https://github.com/olikraus/u8g2/wiki/fntlistall      
*/

#pragma once

#include <Arduino.h>
#include <U8g2lib.h>
#include <SPI.h>

#include "sys.h"
#include "sys_xbmp.h"

#define WIDTH 128
#define HEIGHT 64
#define CTRL_TO 50

U8G2_ST7565_ERC12864_F_4W_SW_SPI u8g2(U8G2_R0, 18, 19, 17, 16, 20);

unsigned long previousMillis = 0;
const long interval = 300;

class Gfx
{
  private:
  public:
    
    /* start gfx */
    void screen()
    {
      u8g2.begin();
      u8g2.setContrast(0);
      sys.backlight(true);
    }

    /* render sys message */
    void renderMessage( void(*draw_fn)(String, String), String a, String b, int timeDelay )
    {
      uint32_t time;
      time = millis() + timeDelay;

      do {
        u8g2.clearBuffer();
        draw_fn(a, b);
        u8g2.sendBuffer();
      } while ( millis() < time );
    }

    /* render gfx */
    void render( void(*draw_fn)(void), int timeDelay )
    {
      uint32_t time;
      time = millis() + timeDelay;

      do {
        u8g2.clearBuffer();
        draw_fn();
        u8g2.sendBuffer();
      } while ( millis() < time );
    }

    void clear()
    {
      u8g2.clearBuffer();
      u8g2.sendBuffer();
    }
};

Gfx gfx;

/* cursor */
bool drawCursor(bool stateCursor)
{
  if (stateCursor == true)
  {
    u8g2.setDrawColor(2);
    u8g2.setBitmapMode(1);
    u8g2.drawXBMP(sys.joi0x(), sys.joi0y(), cursor_w, cursor_h, cursor);
    u8g2.setDrawColor(1);
    u8g2.setBitmapMode(0);
    return true;
  }
  else return false;
}
