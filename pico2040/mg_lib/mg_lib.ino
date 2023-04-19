#include "mg.h"

Systems sys;
Graphics gfx;
Interface inf;

void helloBro()
{
    inf.button("OK", 10, 50);
    gfx.drawCursor(true,sys.joi0x(),sys.joi0y());
    gfx.print("Hello Bro!\nI am a MakeGame!\nWhat is your name?", 10, 20, 10, 6);
}


void setup()
{
    gfx.screen();
    inf.greetings();
}

void loop()
{
    gfx.render(helloBro,0);

    if (sys.sw0())
    {
        inf.messageInfo("You clicked on\nthe Stick 0 button\n:D", 1500, 3, 10, 27);
    }
    if (sys.sw1())
    {
        inf.messageInfo("You clicked on\nthe Stick 1 button", 1500, 2, 10, 27);
    }
}