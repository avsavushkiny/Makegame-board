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
    bool button(String text, uint8_t x, uint8_t y);
};

#endif