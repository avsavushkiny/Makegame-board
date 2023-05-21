#include <mg.h>

Systems sys;
Graphics gfx;
Interface inf;

void helloWorld()
{
    gfx.print("Hello world! Bro!", 0, 10, 8, 5);
    gfx.print("Hello world! Bro!", 0, 20);
    gfx.print("Hello world! Bro!", 0, 30, 8, 8);
}

void setup()
{
    gfx.screen();
    inf.greetingsBoard();
}

void loop()
{
    gfx.render(helloWorld, 0);
}