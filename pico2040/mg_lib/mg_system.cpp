/*    
    Contains the definition of functions
    for working with AD ports.
*/

#include <Arduino.h>
#include "mg.h"

/* system buttons / sw0, sw1 */
bool Systems::sw0()
{
    if (digitalRead(btn_0) == false)
    {
        return true;
    }
    else
        return false;
}

bool Systems::sw1()
{
    if (digitalRead(btn_1) == false)
    {
        return true;
    }
    else
        return false;
}

/* system ADC / joi0y, joi1y, joi0x, joi1x */
int Systems::joi0y() // 0y
{
    dataJoiY0 = analogRead(JOI_0Y);

    if ((dataJoiY0 < (DEF_RES_Y0 - 200)) && (dataJoiY0 > (DEF_RES_Y0 - 1100)))
    {
        return yJoi0 = yJoi0 - 1;
    }
    else if (dataJoiY0 < (DEF_RES_Y0 - 1100))
    {
        return yJoi0 = yJoi0 - 2;
    }
    else if ((dataJoiY0 > (DEF_RES_Y0 + 200)) && (dataJoiY0 < (DEF_RES_Y0 + 1100)))
    {
        return yJoi0 = yJoi0 + 1;
    }
    else if (dataJoiY0 > (DEF_RES_Y0 + 1100))
    {
        return yJoi0 = yJoi0 + 2;
    }
    else
        return yJoi0;
}

int Systems::joi1y() // 1y
{
    dataJoiY1 = analogRead(JOI_1Y);

    if ((dataJoiY1 < (DEF_RES_Y1 - 200)) && (dataJoiY1 > (DEF_RES_Y1 - 1100)))
    {
        return yJoi1 = yJoi1 - 1;
    }
    else if (dataJoiY1 < (DEF_RES_Y1 - 1100))
    {
        return yJoi1 = yJoi1 - 2;
    }
    else if ((dataJoiY1 > (DEF_RES_Y1 + 200)) && (dataJoiY1 < (DEF_RES_Y1 + 1100)))
    {
        return yJoi1 = yJoi1 + 1;
    }
    else if (dataJoiY1 > (DEF_RES_Y1 + 1100))
    {
        return yJoi1 = yJoi1 + 2;
    }
    else
        return yJoi1;
}

int Systems::joi0x() // 0x
{
    dataJoiX0 = analogRead(JOI_X0);

    if ((dataJoiX0 < (DEF_RES_X0 - 200)) && (dataJoiX0 > (DEF_RES_X0 - 1100)))
    {
        return xJoi0 = xJoi0 + 1;
    }
    else if (dataJoiX0 < (DEF_RES_X0 - 1100))
    {
        return xJoi0 = xJoi0 + 2;
    }
    else if ((dataJoiX0 > (DEF_RES_X0 + 200)) && (dataJoiX0 < (DEF_RES_X0 + 1100)))
    {
        return xJoi0 = xJoi0 - 1;
    }
    else if (dataJoiX0 > (DEF_RES_X0 + 1100))
    {
        return xJoi0 = xJoi0 - 2;
    }
    else
        return xJoi0;
}

int Systems::joi1x() // 1x
{
    dataJoiX1 = analogRead(JOI_X1);

    if ((dataJoiX1 < (DEF_RES_X1 - 200)) && (dataJoiX1 > (DEF_RES_X1 - 1100)))
    {
        return xJoi1 = xJoi1 + 1;
    }
    else if (dataJoiX1 < (DEF_RES_X1 - 1100))
    {
        return xJoi1 = xJoi1 + 2;
    }
    else if ((dataJoiX1 > (DEF_RES_X1 + 200)) && (dataJoiX1 < (DEF_RES_X1 + 1100)))
    {
        return xJoi1 = xJoi1 - 1;
    }
    else if (dataJoiX1 > (DEF_RES_X1 + 1100))
    {
        return xJoi1 = xJoi1 - 2;
    }
    else
        return xJoi1;
}

/* Updating Stick coordinates */
void Systems::updateSticks()
{
    s0x = joi0x();
    s0y = joi0y();
    s1x = joi1x();
    s1y = joi1y();
}

/* system backlight */
void Systems::backlight(bool state)
{
    pinMode(aLcd, OUTPUT);

    if (state == true)
    {
        digitalWrite(aLcd, 1); // on
    }
    else
    {
        digitalWrite(aLcd, 0); // off
    }
}

/* oblect - obj0y, obj1y */
int Systems::obj0y() // obj 0y
{
    dataJoiY0 = analogRead(JOI_0Y);

    if ((dataJoiY0 < (DEF_RES_Y0 - 200)) && (dataJoiY0 > (DEF_RES_Y0 - 1100)))
    {
        return objUD0y = objUD0y - 1;
    }
    else if (dataJoiY0 < (DEF_RES_Y0 - 1100))
    {
        return objUD0y = objUD0y - 1; // 2
    }
    else if ((dataJoiY0 > (DEF_RES_Y0 + 200)) && (dataJoiY0 < (DEF_RES_Y0 + 1100)))
    {
        return objUD0y = objUD0y + 1;
    }
    else if (dataJoiY0 > (DEF_RES_Y0 + 1100))
    {
        return objUD0y = objUD0y + 1; // 2
    }
    else
        return objUD0y = 0;
}

int Systems::obj1y() // obj 1y
{
    dataJoiY1 = analogRead(JOI_1Y);

    if ((dataJoiY1 < (DEF_RES_Y1 - 200)) && (dataJoiY1 > (DEF_RES_Y1 - 1100)))
    {
        return objUD1y = objUD1y - 1;
    }
    else if (dataJoiY1 < (DEF_RES_Y1 - 1100))
    {
        return objUD1y = objUD1y - 1; // 2
    }
    else if ((dataJoiY1 > (DEF_RES_Y1 + 200)) && (dataJoiY1 < (DEF_RES_Y1 + 1100)))
    {
        return objUD1y = objUD1y + 1;
    }
    else if (dataJoiY1 > (DEF_RES_Y1 + 1100))
    {
        return objUD1y = objUD1y + 1; // 2
    }
    else
        return objUD1y = 0;
}

/* timer */
unsigned long prevTime{};

void Timer::timer(void (*timer_fn)(void), int interval)
{
    unsigned long currTime = millis();
    if (currTime - prevTime >= interval)
    {
        prevTime = currTime;
        timer_fn();
    }
}