#include "mg.h"

Systems sys;
Graphics gfx;
Interface inf;
Button btn1, btn2, btn3;
Cursor crs1;

void helloSerial()
{
    Serial.println("click button");
}

void helloBro()
{
    sys.sticks();
    
    btn1.button("OK", 10, 50, helloSerial, sys.s0x, sys.s0y);
    btn2.button("CANCEL", 30, 50, NULL, sys.s0x, sys.s0y);
    btn3.button("EXIT", 70, 50, NULL, sys.s0x, sys.s0y);

    crs1.cursor(true, sys.s0x, sys.s0y);
    //crs2.cursor(true);

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

    /*if (sys.sw0())
    {
        inf.messageInfo("You clicked on\nthe Stick 0 button\n:D", 1500, 3, 10, 27);
    }
    if (sys.sw1())
    {
        inf.messageInfo("You clicked on\nthe Stick 1 button", 1500, 2, 10, 27);
    }*/
}