/*
  graphics output library
  ST7565 128*64  

  reference manual https://github.com/olikraus/u8g2/wiki/u8g2reference
  fonts            https://github.com/olikraus/u8g2/wiki/fntlistall      
*/

#pragma once

#include <U8g2lib.h>
//#include <SPI.h>

#include "sys.h"
#include "sys_xbmp.h"

/* def variables */
#define WIDTH 128
#define HEIGHT 64
#define CTRL_TO 50

unsigned long previousMillis = 0;
const long interval = 300;

/* graphics chip setup */
U8G2_ST7565_ERC12864_F_4W_SW_SPI u8g2(U8G2_R0, 18, 19, 17, 16, 20);

/* graphics output objects */
class Gfx
{
private:
  unsigned long prevTime_0{};
public:

  /* initial setting */
  void screen()
  {
    u8g2.begin();
    u8g2.setContrast(0);
    sys.backlight(true);
  }
  
  /* data render */
  void render(void (*ptr_draw_fn)(), int timeDelay)
  {
    uint32_t time;
    time = millis() + timeDelay;

    do
    {
      u8g2.clearBuffer();
      ptr_draw_fn();
      u8g2.sendBuffer();
    } while (millis() < time);
  }

  /* clearing the output buffer */
  void clear()
  {
    u8g2.clearBuffer();
    u8g2.sendBuffer();
  }

  /* text output with parameters */
  void print(String text, int x, int y, int lii, int chi) // text, x-position, y-position, line interval (8-10), character interval (4-6)
  {
    int sizeText = text.length() + 1;
    int yy{ 0 };
    
    for (int i = 0, xx = 0; i < sizeText, xx < (sizeText * chi); i++, xx += chi)
    {
      u8g2.setFont(u8g2_font_6x10_tr);
      u8g2.setCursor(xx + x, yy + y);
      u8g2.print(text[i]);

      if (text[i] == '\n')
      {
        yy += lii; //10
        xx = -chi; //6
      }
    }
  }

  /* "wink text" output  */
  bool winkPrint(void(*ptr_fn)(String, int, int), String text, int x, int y, /*delay*/ int interval)
  {
    unsigned long currTime = millis();
    if (currTime - prevTime_0 >= interval)
    {
      prevTime_0 = currTime; return 0;
    }
    else
    {
      ptr_fn(text, x, y); return 1;
    }
  }

  /* displaying the cursor on the screen */
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
    } else return false;
  }
};

Gfx gfx;

/* text output without parameters */
void printf(String text, int x, int y)
{
  int sizeText = text.length() + 1;
  int yy{ 0 };
    
  for (int i = 0, xx = 0; i < sizeText, xx < (sizeText * 6); i++, xx += 6)
  {
    u8g2.setFont(u8g2_font_6x10_tr); 
    u8g2.setCursor(xx + x, yy + y);
    u8g2.print(text[i]);

    if (text[i] == '\n')
    {
      yy += 10;
      xx = -6;
    }
  }
}

/*
//old version function - print

char text[] = "Hey Bro!\nI am Console,\nOpen source project!";

void print()
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
}

//old version function - renderMessage
void renderMessage(void (*draw_fn)(String, String), String a, String b, int timeDelay)
{
  uint32_t time;
  time = millis() + timeDelay;

  do
  {
    u8g2.clearBuffer();
    draw_fn(a, b);
    u8g2.sendBuffer();
  } while (millis() < time);
}

*/