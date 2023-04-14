#include "mg.h"

Systems sys;
Graphics gfx;

void hello()
{
    gfx.drawCursor(true,sys.joi0x(),sys.joi0y());
    gfx.print("text\ntext2", 10, 10, 10, 6);
}


void setup()
{
    gfx.screen();
}

void loop()
{
    gfx.render(hello,0);

    if (sys.sw0())
    {
        Serial.println("hello");
    }
}