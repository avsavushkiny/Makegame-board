/*
  Contains function settings for working with the display.

  [!] Required u8g2 library
  [!] bmp to xbmp image converter https://www.online-utility.org/image/convert/to/XBM
*/

#include <Arduino.h>
#include <U8g2lib.h> 
#include "mg.h"

extern Systems _sys;

const uint8_t WIDTH_LCD = 128;
const uint8_t HEIGHT_LCD = 64;

const int8_t aLcd = 8;

unsigned long previousMillis = 0;
unsigned long prevTime_0{};
const long interval = 300;

/* cursor */
#define cursor_w 7
#define cursor_h 8
const uint8_t cursor_bits[] = {
  0x03, 0x05, 0x09, 0x11, 0x21, 0x79, 0x05, 0x03, };

/* logotype makegame */
#define mg_l_w 56
#define mg_l_h 28
const uint8_t mg_l_bits[] = {
  0x0C, 0x0C, 0xFC, 0xC0, 0xF3, 0xF0, 0x3F, 0x0C, 0x0C, 0xFC, 0xC0, 0xF3, 
  0xF0, 0x3F, 0x33, 0x33, 0x03, 0x33, 0x0C, 0x0F, 0xC0, 0x33, 0x33, 0x03, 
  0x33, 0x0C, 0x0F, 0xC0, 0xC3, 0xF0, 0x30, 0x3C, 0xC0, 0x0C, 0x3C, 0xC3, 
  0xF0, 0x30, 0x3C, 0xC0, 0x0C, 0x3C, 0x03, 0xF0, 0x00, 0x3C, 0x30, 0x0C, 
  0x30, 0x03, 0xF0, 0x30, 0x3C, 0x30, 0x0C, 0x30, 0x33, 0xF3, 0x30, 0x3C, 
  0xC0, 0x0C, 0x3C, 0x33, 0xF3, 0x30, 0x3C, 0xC0, 0x0C, 0x3C, 0xF3, 0xF3, 
  0x30, 0x3C, 0x0C, 0x0F, 0xC0, 0xF3, 0xF3, 0x30, 0x3C, 0x0C, 0x0F, 0xC0, 
  0x0C, 0x0C, 0xCF, 0xC3, 0xF3, 0xF0, 0x3F, 0x0C, 0x0C, 0xCF, 0xC3, 0xF3, 
  0xF0, 0x3F, 0xF0, 0x0F, 0xFC, 0xC0, 0xC0, 0xF0, 0x3F, 0xF0, 0x0F, 0xFC, 
  0xC0, 0xC0, 0xF0, 0x3F, 0x0C, 0x30, 0x03, 0x33, 0x33, 0x0F, 0xC0, 0x0C, 
  0x30, 0x03, 0x33, 0x33, 0x0F, 0xC0, 0xC3, 0xCF, 0x30, 0x3C, 0x0C, 0x0F, 
  0x3C, 0xC3, 0xCF, 0x30, 0x3C, 0x0C, 0x0F, 0x3C, 0xC3, 0xF0, 0x00, 0x3C, 
  0x00, 0x0F, 0x30, 0xC3, 0xF0, 0x30, 0x3C, 0x00, 0x0F, 0x30, 0xC3, 0xF3, 
  0x30, 0x3C, 0x33, 0x0F, 0x3C, 0xC3, 0xF3, 0x30, 0x3C, 0x33, 0x0F, 0x3C, 
  0x0C, 0xF0, 0x30, 0x3C, 0x3F, 0x0F, 0xC0, 0x0C, 0xF0, 0x30, 0x3E, 0x3F, 
  0x0F, 0xC0, 0xF0, 0x3F, 0xCF, 0xC3, 0xC0, 0xF0, 0x3F, 0xF0, 0x3F, 0xCF, 
  0xC3, 0xC0, 0xF0, 0x3F, };

/* logotype terminal */
#define trm_l_w 11
#define trm_l_h 9
const uint8_t trm_l_bits[] = {
  0xFE, 0x03, 0x01, 0x04, 0x05, 0x04, 0x09, 0x04, 0x11, 0x04, 0x09, 0x04, 
  0xC5, 0x05, 0x01, 0x04, 0xFE, 0x03, };

/* qr-code @avsavushkiny/makegame-board */
#define qr_w 33
#define qr_h 33
const uint8_t qr_bits[] = {
  0x7F, 0x2F, 0xBB, 0xFC, 0x01, 0x41, 0x25, 0xB5, 0x05, 0x01, 0x5D, 0x18, 
  0x53, 0x75, 0x01, 0x5D, 0x55, 0x51, 0x74, 0x01, 0x5D, 0x72, 0x12, 0x75, 
  0x01, 0x41, 0x5E, 0x7A, 0x05, 0x01, 0x7F, 0x55, 0x55, 0xFD, 0x01, 0x00, 
  0x59, 0x96, 0x00, 0x00, 0xED, 0x4E, 0x7F, 0xA5, 0x01, 0x2F, 0x5D, 0xBD, 
  0x6C, 0x01, 0x69, 0x59, 0xC3, 0xBA, 0x01, 0xA3, 0xE7, 0x4D, 0x28, 0x00, 
  0xF9, 0x12, 0xA4, 0xBB, 0x01, 0x0C, 0x2B, 0x27, 0xA9, 0x00, 0x6C, 0xD1, 
  0x21, 0x3D, 0x00, 0x29, 0x78, 0xB9, 0x6E, 0x00, 0xCF, 0xD3, 0x7C, 0x76, 
  0x00, 0x9E, 0xCF, 0xF6, 0xB7, 0x00, 0x55, 0x92, 0x52, 0xDB, 0x00, 0x26, 
  0x6B, 0xA8, 0x97, 0x00, 0xEF, 0x96, 0x14, 0x62, 0x01, 0x8B, 0xD0, 0xA4, 
  0x04, 0x01, 0x64, 0x4F, 0xA5, 0xDE, 0x01, 0x8E, 0x54, 0x89, 0xBC, 0x01, 
  0x6D, 0xDB, 0x42, 0x9F, 0x01, 0x00, 0xC7, 0x1F, 0x31, 0x00, 0x7F, 0x69, 
  0xD8, 0x95, 0x00, 0x41, 0x69, 0xF0, 0xF1, 0x00, 0x5D, 0x14, 0x9A, 0x5F, 
  0x00, 0x5D, 0x03, 0xBC, 0xA8, 0x01, 0x5D, 0x05, 0x48, 0x6C, 0x00, 0x41, 
  0xDC, 0xCF, 0x1B, 0x01, 0x7F, 0xE3, 0xA6, 0x50, 0x00, };

/* icon: icon */
#define icon_wi 8
#define icon_h 8
const uint8_t icon_bits[] = {
  0xFF, 0x81, 0xBD, 0xB9, 0xBD, 0xAD, 0x81, 0xFF, };

/* icon: gears */
#define gears_w 32
#define gears_h 32
const uint8_t gears_bits[] = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3C, 0x00, 0x00, 
  0x00, 0x42, 0x00, 0x00, 0x00, 0x42, 0x00, 0x00, 0x60, 0x5A, 0x06, 0x00, 
  0x90, 0xC3, 0x09, 0x00, 0x10, 0x42, 0x08, 0x00, 0x30, 0x42, 0x0C, 0x00, 
  0x30, 0xC3, 0x0C, 0x00, 0x9C, 0x42, 0x39, 0x00, 0x02, 0xC3, 0x40, 0x00, 
  0x1E, 0x7E, 0x78, 0x00, 0x12, 0x00, 0x84, 0x00, 0x1C, 0xC3, 0x84, 0x0C, 
  0xB0, 0x24, 0xB7, 0x13, 0xD0, 0x25, 0x84, 0x10, 0xD0, 0x7E, 0x84, 0x18, 
  0x60, 0x64, 0x86, 0x19, 0x00, 0x3C, 0x85, 0x72, 0x00, 0x04, 0x86, 0x81, 
  0x00, 0x3C, 0xFC, 0xF0, 0x00, 0x2C, 0x00, 0xB0, 0x00, 0x38, 0x86, 0x71, 
  0x00, 0x60, 0xCF, 0x1B, 0x00, 0xA0, 0xCF, 0x17, 0x00, 0xA0, 0xFD, 0x16, 
  0x00, 0xC0, 0x48, 0x0C, 0x00, 0x00, 0x78, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, };

/* graphics chip setup */
U8G2_ST7565_ERC12864_F_4W_SW_SPI u8g2(U8G2_R0, 18, 19, 17, 16, 20);

/* graphics */
/* graphics output objects */
void Graphics::screen()
{
    u8g2.begin();
    u8g2.setContrast(0);
    analogReadResolution(12);

    pinMode(aLcd, OUTPUT);
    digitalWrite(aLcd, true);
}

/* data render */
void Graphics::render(void (*draw_fn)(), int timeDelay)
{
    uint32_t time;

    time = millis() + timeDelay;

    do
    {
        u8g2.clearBuffer();
        draw_fn();
        u8g2.sendBuffer();
    } while (millis() < time);
}

/* clearing the output buffer */
void Graphics::clear()
{
    u8g2.clearBuffer();
    u8g2.sendBuffer();
}

/* print */
/* text output with parameters, add line interval (def: 10) and character interval (def: 6) */
void Graphics::print(String text, int x, int y, int lii, int chi) // text, x-position, y-position, line interval (8-10), character interval (4-6)
{
    int sizeText = text.length() + 1;
    int yy{0};

    for (int i = 0, xx = 0; i < sizeText, xx < (sizeText * chi); i++, xx += chi)
    {
        u8g2.setFont(u8g2_font_6x10_tr);
        u8g2.setCursor(xx + x, yy + y);
        u8g2.print(text[i]);

        if (text[i] == '\n')
        {
            yy += lii; // 10
            xx = -chi; // 6
        }
    }
}

/* text output with parameters */
void Graphics::print(String text, int x, int y) // text, x-position, y-position, line interval (8-10), character interval (4-6)
{
    int8_t lii{10}, chi{6};
    int sizeText = text.length() + 1;
    int yy{0};

    for (int i = 0, xx = 0; i < sizeText, xx < (sizeText * chi); i++, xx += chi)
    {
        u8g2.setFont(u8g2_font_6x10_tr);
        u8g2.setCursor(xx + x, yy + y);
        u8g2.print(text[i]);

        if (text[i] == '\n')
        {
            yy += lii; // 10
            xx = -chi; // 6
        }
    }
}

/* "wink text" output  */
bool Graphics::winkPrint(void (*ptr_fn)(String, int, int), String text, int x, int y, int interval)
{
    unsigned long currTime = millis();
    if (currTime - prevTime_0 >= interval)
    {
        prevTime_0 = currTime;
        return 0;
    }
    else
    {
        ptr_fn(text, x, y);
        return 1;
    }
}

/* displaying the cursor on the screen */
bool Cursor::cursor(bool stateCursor, int xCursor, int yCursor)
{
    if (stateCursor == true)
    {
        u8g2.setDrawColor(2);
        u8g2.setBitmapMode(1);
        u8g2.drawXBMP(xCursor, yCursor, cursor_w, cursor_h, cursor_bits);
        u8g2.setDrawColor(1);
        u8g2.setBitmapMode(0);
        return true;
    }
    else
        return false;
}

/* text output without parameters */
void Graphics::printf(String text, int x, int y)
{
    int sizeText = text.length() + 1;
    int yy{0};

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

Graphics _gfx;
//Systems _sys;

/* interface */
void _frame_1()
{
    u8g2.drawXBMP(36, 18, mg_l_w, mg_l_h, mg_l_bits);
}

void Interface::greetingsBoard()
{
    u8g2.clearBuffer();
    _frame_1();
    u8g2.sendBuffer();
    delay(2500);
}

void Interface::message(String text, int duration)
{
    uint8_t x{10}, y{34};
    
    /* Counting the number of lines in a message
       Line break is supported - '\n' */   
    int sizeText = text.length() + 1, line{};

    for (int i = 0; i < sizeText; i++)
    {
        if (text[i] == '\n')
        {
          line++;
        }
    }

    uint8_t correction = (line * 10)/2;
    
    u8g2.clearBuffer();
    for (int i = 0; i < WIDTH_LCD; i += 2)
    {
        for (int j = 0; j < (y - 10) - correction; j += 2)
        {
            u8g2.drawPixel(i, j);
        }

        for (int k = y + ((line) * 10) + 4 - correction /* correction */; k < HEIGHT_LCD; k += 2)
        {
            u8g2.drawPixel(i, k);
        }
    }

    _gfx.print(text, x, y - correction, 10, 6);
    u8g2.sendBuffer();

    delay(duration);
}

/* button */
bool Button::button(String text, uint8_t x, uint8_t y, void (*f)(void), int xCursor, int yCursor)
{
  uint8_t sizeText = text.length();

  if ((xCursor >= x && xCursor <= (x + (sizeText * 5) + 4)) && (yCursor >= y - 8 && yCursor <= y + 2))
  {
    u8g2.setDrawColor(1);
    u8g2.drawRBox(x, y - 8, (sizeText * 5) + 5, 10, 2);

    if (Systems::sw0())
    {
      f();
      return true;
    }
  }
  else
  {
    u8g2.setDrawColor(1);
    u8g2.drawRFrame(x, y - 8, (sizeText * 5) + 5, 10, 2);
  }

  u8g2.setCursor(x + 3, y);
  u8g2.setFont(u8g2_font_profont10_mr);
  u8g2.setFontMode(1);
  u8g2.setDrawColor(2);
  u8g2.print(text);
  u8g2.setFontMode(0);
  
  return false;
}

bool Button::button(String text, uint8_t x, uint8_t y, void (*f)(void))
{
  xCursor = _sys.s0x; yCursor = _sys.s0y;
  
  uint8_t sizeText = text.length();

  if ((xCursor >= x && xCursor <= (x + (sizeText * 5) + 4)) && (yCursor >= y - 8 && yCursor <= y + 2))
  {
    u8g2.setDrawColor(1);
    u8g2.drawRBox(x, y - 8, (sizeText * 5) + 5, 10, 2);

    if (Systems::sw0())
    {
      f();
      return true;
    }
  }
  else
  {
    u8g2.setDrawColor(1);
    u8g2.drawRFrame(x, y - 8, (sizeText * 5) + 5, 10, 2);
  }

  u8g2.setCursor(x + 3, y);
  u8g2.setFont(u8g2_font_profont10_mr);
  u8g2.setFontMode(1);
  u8g2.setDrawColor(2);
  u8g2.print(text);
  u8g2.setFontMode(0);
  
  return false;
}

/* shortcut */
bool Shortcut::shortcut(const uint8_t *bitMap, uint8_t x, uint8_t y, void (*f)(void), int xCursor, int yCursor)
{
  u8g2.setDrawColor(1);
  u8g2.setBitmapMode(0);
  u8g2.drawXBMP(x, y, 32, 32, bitMap);
  u8g2.drawXBMP(x, y + 24, 8, 8, icon_bits);

  if ((xCursor >= x && xCursor <= (x + 32)) && (yCursor >= y && yCursor <= (y + 32)))
  {
    u8g2.drawFrame(x, y, 32, 32);
    if (Systems::sw0())
    {
      f();
      return true;
    }
  }

  return false;
}

/* terminal */
/* prototype */
void clearCommandTerminal();

/* command type */
struct Command
{
  char const *text;
  void (*f)();
  bool active;
};

/* enumeration of objects - commands */
Command commands[]{
    {"clrcom", clearCommandTerminal, false}
};

/* delete all commands */
void clearCommandTerminal()
{
  for (Command &command : commands)
  {
    command.active = false;
  }
}

/* command stack */
void _calcTerminal()
{
  for (Command &command : commands)
  {
    if (command.active)
    {
      command.f();
    }
  }
}

/* pushing data onto the stack */
void Terminal::terminal()
{
  _gfx.render(_calcTerminal, 0);

  if (Serial.available() != 0)
  {
    char text[10]{};
    Serial.readBytesUntil('\n', text, sizeof(text));

    for (Command &command : commands)
    {
      if (not strncmp(command.text, text, 10))
      {
        command.active = true;
      }
    }
  }
}