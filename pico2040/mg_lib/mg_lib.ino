#include "mg.h"

Systems sys;


void setup()
{

}

void loop()
{
    if (sys.sw0())
    {
        Serial.println("hello");
    }

}