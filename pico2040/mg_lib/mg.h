/*
    Library for MakeGame board.

    [!] Educational version
    [!] Required u8g2 library

    author: Savushkin Alexander
    git:    @avsavushkiny
    e-mail: avsavushkiny@live.ru
    date:   06.05.2023
*/

#include <U8g2lib.h>

/* We let the compiler know that the u8g2 object is defined in another file */
extern U8G2_ST7565_ERC12864_F_4W_SW_SPI u8g2;
extern const uint8_t gears_bits[];

#ifndef MAKEGAME_H
#define MAKEGAME_H

class Systems
{
private:
    /* The sticks are in the middle position. */
    int DEF_RES_Y0 = 2100;
    int DEF_RES_Y1 = 2100;
    int DEF_RES_X0 = 2100;
    int DEF_RES_X1 = 2100;
    /* Correction on the y0-axis. */
    const int8_t CORR_y0 = 100;
    /* Port data. */
    const int8_t JOI_X0 = 26; // adc 0
    const int8_t JOI_0Y = 27; // adc 1
    const int8_t JOI_1Y = 28; // adc 2
    const int8_t JOI_X1 = 29; // adc 3
    const int8_t btn_0  = 6;  // gp 6
    const int8_t btn_1  = 7;  // gp 7
    const int8_t aLcd   = 8;  // gp 8
    /* Field (lcd) resolution. */
    int H_RES = 64;
    int W_RES = 128;
    /* Initial setting of coordinates. */
    int yJoi0 = H_RES / 2;
    int yJoi1 = H_RES / 2;
    int xJoi0 = W_RES / 2;
    int xJoi1 = W_RES / 2;
    /* Reset the counter of objects. */
    int objUD0y{};
    int objUD1y{};
    int objUD0x{};
    int objUD1x{};
    /* Raw data from Sticks. */
    int dataJoiY0{};
    int dataJoiY1{};
    int dataJoiX0{};
    int dataJoiX1{};
    /* Contains the coordinates of the Sticks along the axes. */
    int joi0y();
    int joi1y();
    int joi0x();
    int joi1x();
public:
    /* Variables for storing coordinates from the axes of the Sticks. */
    int s0x, s0y, s1x, s1y;
    /* Generates 1 or 0 if the button is pressed or not. */
    bool sw0();
    bool sw1();
    /* Updating Stick coordinates. */
    void updateSticks();
    /* Turn on the backlight of the LCD screen. 1 enabled, 0 disabled. */
    void backlight(bool state);
    /* Counts objects by +1, normally 0 */
    int obj0y();
    int obj1y();
protected:
};

class Graphics
{
private:
public:
    /* Initial display setting. Sets Contrast to 0, analog DC at 12, sets port 8 to 1 */
    void screen();
    /* We send the void-function to the display buffer for output. 
       The void-function will be completed by time-Delay-interval. */
    void render(void (*ptr_draw_fn)(), int timeDelay);
    /* Clearing the display buffer. */
    void clear();
    /* Data output in x, y coordinates. lii-line spacing (10 by default),
       chi-character spacing (6 by default).
       Line break is supported - '\n' */
    void print(String text, int x, int y, int lii, int chi);
    /* Runs a void-function with text-string and output x-y-coordinates parameters.
       The interval-interval controls the output. */
    bool winkPrint(void (*ptr_fn)(String, int, int), String text, int x, int y, /*delay*/ int interval);
    /* Text output with newline '\n' support. */
    void printf(String text, int x, int y); 
};

class Timer
{
private:
public:
    /* Starting a void-function on a interval-timer. */
    void timer(void (*timer_fn)(void), int interval);
};

class Terminal
{
private:
public:
    void terminal();
};

class Interface
{
private:
public:
    /* Greetings. Contains logo and text. */
    void greetings();
    /* Sending a text-message to the user.
       Determine the duration-duration and x-y-coordinates of the output.
       Line break is supported - '\n'. */
    void message(String text, int duration, uint8_t x, uint8_t y);
};

class Button : Systems
{
private:
    int xCursor, yCursor;
public:
    /* The button starts the void-function, define the button text-text and output x-y-coordinates.
       Cursor xCursor-yCursor-coordinates must be specified. */
    bool button(String text, uint8_t x, uint8_t y, void (*f)(void), int xCursor, int yCursor);
};

class Shortcut : Systems
{
private:
public:
    bool shortcut(const uint8_t *icon, uint8_t x, uint8_t y, void (*f)(void), int xCursor, int yCursor);
};

class Cursor : Systems
{
private:
public:
    /* Cursor. If the stateCursor-status is 1 - is displayed, if 0 - then not. */
    bool cursor(bool stateCursor, int xCursor, int yCursor);
};

#endif