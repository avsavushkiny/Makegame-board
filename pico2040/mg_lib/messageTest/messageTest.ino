#include <mg.h>

Systems sys;
Graphics gfx;
Interface inf;

void message()
{
    gfx.print("Press the button\nof the first Stick", 0, 10, 10, 5);
}

void setup()
{
    gfx.screen();
    inf.greetingsBoard();
}

void loop()
{
    gfx.render(message, 0);

    if (sys.sw0() == true)
    {
        inf.message("Supports multiline\nmessage", 1500);
    }
}