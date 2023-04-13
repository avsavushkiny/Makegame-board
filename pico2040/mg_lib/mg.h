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
};

#endif