/*
    Library for MakeGame board.

    [!] Educational version
    [!] Required u8g2 library

    author: Savushkin Alexander
    git:    @avsavushkiny
    e-mail: avsavushkiny@live.ru
    date:   06.06.2023
*/

#include <U8g2lib.h>

/* We let the compiler know that the u8g2 object is defined in another file */
extern U8G2_ST7565_ERC12864_F_4W_SW_SPI u8g2;
extern const uint8_t gears_bits[];

#ifndef MAKEGAME_H
#define MAKEGAME_H

class Systems
{
protected:
    /* Port data. */
    const int8_t PIN_STICK_0X = 26; // adc 0
    const int8_t PIN_STICK_0Y = 27; // adc 1
    const int8_t PIN_STICK_1Y = 28; // adc 2
    const int8_t PIN_STICK_1X = 29; // adc 3
    const int8_t PIN_BUTTON_STICK_0 = 6;  // gp 6
    const int8_t PIN_BUTTON_STICK_1 = 7;  // gp 7
    const int8_t PIN_BACKLIGHT_LCD = 8;   // gp 8
    /* Liquid crystal display resolution. */
    int HEIGHT_LCD{64}, WIDTH_LCD{128};
    /* Analog-to-digital converter resolution (Chip PICO 2040). */
    const int8_t RESOLUTION_ADC{12};
private:
    /* The sticks are in the middle position. */
    int DEF_RES_Y0{2100}, DEF_RES_Y1{2100}, DEF_RES_X0{2100}, DEF_RES_X1{2100};
    /* Correction on the y0-axis. */
    const int8_t CORR_Y0{100}, CORR_Y1{100};
    /* Initial setting of coordinates. */
    int COOR_Y0 = HEIGHT_LCD / 2; 
    int COOR_Y1 = HEIGHT_LCD / 2;
    int COOR_X0 = WIDTH_LCD  / 2;
    int COOR_X1 = WIDTH_LCD  / 2;
    /* Reset the counter of objects. */
    int OBJ_Y0{}, OBJ_Y1{}, OBJ_X0{}, OBJ_X1{};
    /* Raw data from Sticks. */
    int RAW_DATA_Y0{}, RAW_DATA_Y1{}, RAW_DATA_X0{}, RAW_DATA_X1{};
    /* Contains the coordinates of the Sticks along the axes. */
    int calculateStickPosition0Y(); //calculateJoystickCoordinates
    int calculateStickPosition1Y();
    int calculateStickPosition0X();
    int calculateStickPosition1X();
public:
    /* Variables for storing coordinates from the axes of the Sticks. */
    int stickPosX0, stickPosY0, stickPosX1, stickPosY1; // xPosStick0, posStckXs0, 
    /* Generates 1 or 0 if the button is pressed or not. */
    bool keyA();
    bool keyB();
    /* Updating Stick coordinates. */
    void updateSticksPosition();
    /* Turn on the backlight of the LCD screen. 1 enabled, 0 disabled. */
    void backlightControl(bool state);
    /* Counts objects by +1, normally 0 */
    int8_t countingObjectStickPosition0Y();
    int8_t countingObjectStickPosition1Y();
    int8_t countingObjectStickPosition0X();
    int8_t countingObjectStickPosition1X();
};

class Graphics : Systems
{
protected:
private:
public:
    /* Initial display setting. Sets Contrast to 0, analog DC at 12, sets port 8 to 1 */
    void initializationSystem();
    /* We send the void-function to the display buffer for output. 
       The void-function will be completed by time-Delay-interval. */
    void render(void (*f)(), int timeDelay);
    /* We send the void-function to the display buffer for output. */
    void render(void (*f)());
    /* Clearing the display buffer. */
    void clear();
    /* Data output in x, y coordinates. lii-line spacing (10 by default),
       chi-character spacing (6 by default).
       Line break is supported - '\n' */
    void print(String text, int x, int y, int lii, int chi);
    /* Data output in x, y coordinates. 
       Line break is supported - '\n' */
    void print(String text, int x, int y);
    /* Runs a void-function with text-string and output x-y-coordinates parameters.
       The interval-interval controls the output. */
    bool winkPrint(void (*f)(String, int, int), String text, int x, int y, /*delay*/ int interval);
};

class Timer
{
protected:
private:
    unsigned long prevTime{};
public:
    /* Starting a void-function on a interval-timer. */
    void timer(void (*f)(void), int interval);
};

class Terminal
{
private:
public:
    void terminal();
};

class Interface : Systems
{
private:
public:
    /* Greetings. Contains logo and text. */
    void greetingsBoard();
    /* Output of a message to the user. Define the text-text and duration-duration.
       Line break is supported - '\n'. */
    void message(String text, int duration);
};

class Button : Systems
{
private:
    int xCursor, yCursor;
public:
    /* The button starts the void-function, define the button text-text and output x-y-coordinates.
       xCursor-yCursor-coordinates of interaction with the cursor. */
    bool button(String text, uint8_t x, uint8_t y, void (*f)(void), int xCursor, int yCursor);
};

class Shortcut : Systems
{
private:
public:
    /* A shortcut on the desktop to launch the void-function.
       Define an icon-image with a resolution of 32x32 pixels, x-y-coordinates for output,
       xCursor-yCursor-coordinates of interaction with the cursor. */
    bool shortcut(const uint8_t *bitMap, uint8_t x, uint8_t y, void (*f)(void), int xCursor, int yCursor);
};

class Cursor : Systems
{
private:
public:
    /* Cursor. If the stateCursor status is 1 - visible, if 0 - not visible.
       Determine the coordinates of the Cursor to interact with the selected Stick. */
    bool cursor(bool stateCursor, int xCursor, int yCursor);
};

#endif