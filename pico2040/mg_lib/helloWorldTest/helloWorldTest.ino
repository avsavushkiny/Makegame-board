#include <mg.h>

Systems sys;
Graphics gfx;
Interface inf;

void helloWorld()
{
    gfx.print("hello world!", 0, 10);
    gfx.print("hello world\nBro!", 0, 20, 8, 5);
}

void setup()
{
    gfx.screen();
    gfx.greetingsBoard();

}
void loop()
{
    gfx.render(helloWorld, 0);
}