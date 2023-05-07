#include "mg.h"

Systems sys;
Graphics gfx;
Interface inf;
Button btn1, btn2;
Cursor crs1;

void clickBtn1()
{
    inf.message("You clicked on\nthe Stick 0 button\n:D", 1500, 10, 27);
}

void clickBtn2()
{
    inf.message("Okay :((\nplease Exit!", 1500, 10, 27);
}

void helloBro()
{
    sys.sticks();
    
    btn1.button("OK", 10, 50, clickBtn1, sys.s0x, sys.s0y);
    btn2.button("CANCEL", 30, 50, clickBtn2, sys.s0x, sys.s0y);
 
    crs1.cursor(true, sys.s0x, sys.s0y);
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