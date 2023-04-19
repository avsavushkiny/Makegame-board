/*
    Library for MakeGame board.

    [!] Educational version
    [!] Required u8g2 library

    author: Savushkin Alexander
    git:    @avsavushkiny
    e-mail: avsavushkiny@live.ru
    date:   18.04.2023
*/

#ifndef MG_H
#define MG_H

class Systems
{
private:
    int DEF_RES_Y0 = 2100;
    int DEF_RES_Y1 = 2100;
    int DEF_RES_X0 = 2100;
    int DEF_RES_X1 = 2100;

    const int8_t CORR_y0 = 100;

    const int8_t JOI_X0 = 26; // adc 0
    const int8_t JOI_0Y = 27; // adc 1
    const int8_t JOI_1Y = 28; // adc 2
    const int8_t JOI_X1 = 29; // adc 3

    const int8_t btn_0 = 6; // gp 6
    const int8_t btn_1 = 7; // gp 7
    const int8_t aLcd = 8;  // gp 8

    int H_RES = 64;
    int W_RES = 128;

    int yJoi0 = H_RES / 2;
    int yJoi1 = H_RES / 2;
    int xJoi0 = W_RES / 2;
    int xJoi1 = W_RES / 2;

    int objUD0y{};
    int objUD1y{};
    int objUD0x{};
    int objUD1x{};

    int dataJoiY0{};
    int dataJoiY1{};
    int dataJoiX0{};
    int dataJoiX1{};

public:
    bool sw0();
    bool sw1();

    int joi0y();
    int joi1y();
    int joi0x();
    int joi1x();

    void backlight(bool state);

    int obj0y();
    int obj1y();
};

class Timer
{
private:
public:
    void timer(void (*timer_fn)(void), int interval);
};

class Graphics
{
private:
public:
    void screen();
    void render(void (*ptr_draw_fn)(), int timeDelay);
    void clear();
    void print(String text, int x, int y, int lii, int chi);
    bool winkPrint(void (*ptr_fn)(String, int, int), String text, int x, int y, /*delay*/ int interval);
    bool drawCursor(bool stateCursor, int sysJoi0x, int sysJoi0y);
    void printf(String text, int x, int y);
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
    void greetings();
    void messageInfo(String text, int del, uint8_t col, uint8_t x, uint8_t y);
};

class Button
{
private:
public:
    bool button(String text, uint8_t x, uint8_t y, void (*f)(void));
};

#endif