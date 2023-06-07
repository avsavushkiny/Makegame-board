/*    
    Contains the definition of functions
    for working with AD ports.
*/

#include <Arduino.h>
#include "mg.h"

/* system button control */
bool Systems::keyStick0()
{
    if (digitalRead(PIN_BUTTON_STICK_0) == false)
    {
        return true;
    }
    else
        return false;
}

bool Systems::keyStick1()
{
    if (digitalRead(PIN_BUTTON_STICK_1) == false)
    {
        return true;
    }
    else
        return false;
}

/* calculate Stick position */
int Systems::calculateStickPosition0Y() // 0y
{
    RAW_DATA_Y0 = analogRead(PIN_STICK_0Y);

    if ((RAW_DATA_Y0 < (DEF_RES_Y0 - 200)) && (RAW_DATA_Y0 > (DEF_RES_Y0 - 1100)))
    {
        return COOR_Y0 = COOR_Y0 - 1;
    }
    else if (RAW_DATA_Y0 < (DEF_RES_Y0 - 1100))
    {
        return COOR_Y0 = COOR_Y0 - 2;
    }
    else if ((RAW_DATA_Y0 > (DEF_RES_Y0 + 200)) && (RAW_DATA_Y0 < (DEF_RES_Y0 + 1100)))
    {
        return COOR_Y0 = COOR_Y0 + 1;
    }
    else if (RAW_DATA_Y0 > (DEF_RES_Y0 + 1100))
    {
        return COOR_Y0 = COOR_Y0 + 2;
    }
    else
        return COOR_Y0;
}

int Systems::calculateStickPosition1Y() // 1y
{
    RAW_DATA_Y1 = analogRead(PIN_STICK_1Y);

    if ((RAW_DATA_Y1 < (DEF_RES_Y1 - 200)) && (RAW_DATA_Y1 > (DEF_RES_Y1 - 1100)))
    {
        return COOR_Y1 = COOR_Y1 - 1;
    }
    else if (RAW_DATA_Y1 < (DEF_RES_Y1 - 1100))
    {
        return COOR_Y1 = COOR_Y1 - 2;
    }
    else if ((RAW_DATA_Y1 > (DEF_RES_Y1 + 200)) && (RAW_DATA_Y1 < (DEF_RES_Y1 + 1100)))
    {
        return COOR_Y1 = COOR_Y1 + 1;
    }
    else if (RAW_DATA_Y1 > (DEF_RES_Y1 + 1100))
    {
        return COOR_Y1 = COOR_Y1 + 2;
    }
    else
        return COOR_Y1;
}

int Systems::calculateStickPosition0X() // 0x
{
    RAW_DATA_X0 = analogRead(PIN_STICK_0X);

    if ((RAW_DATA_X0 < (DEF_RES_X0 - 200)) && (RAW_DATA_X0 > (DEF_RES_X0 - 1100)))
    {
        return COOR_X0 = COOR_X0 + 1;
    }
    else if (RAW_DATA_X0 < (DEF_RES_X0 - 1100))
    {
        return COOR_X0 = COOR_X0 + 2;
    }
    else if ((RAW_DATA_X0 > (DEF_RES_X0 + 200)) && (RAW_DATA_X0 < (DEF_RES_X0 + 1100)))
    {
        return COOR_X0 = COOR_X0 - 1;
    }
    else if (RAW_DATA_X0 > (DEF_RES_X0 + 1100))
    {
        return COOR_X0 = COOR_X0 - 2;
    }
    else
        return COOR_X0;
}

int Systems::calculateStickPosition1X() // 1x
{
    RAW_DATA_X1 = analogRead(PIN_STICK_1X);

    if ((RAW_DATA_X1 < (DEF_RES_X1 - 200)) && (RAW_DATA_X1 > (DEF_RES_X1 - 1100)))
    {
        return COOR_X1 = COOR_X1 + 1;
    }
    else if (RAW_DATA_X1 < (DEF_RES_X1 - 1100))
    {
        return COOR_X1 = COOR_X1 + 2;
    }
    else if ((RAW_DATA_X1 > (DEF_RES_X1 + 200)) && (RAW_DATA_X1 < (DEF_RES_X1 + 1100)))
    {
        return COOR_X1 = COOR_X1 - 1;
    }
    else if (RAW_DATA_X1 > (DEF_RES_X1 + 1100))
    {
        return COOR_X1 = COOR_X1 - 2;
    }
    else
        return COOR_X1;
}

/* Updating Stick coordinates */
void Systems::updateSticksPosition()
{
    stickPosX0 = calculateStickPosition0X();
    stickPosY0 = calculateStickPosition0Y();
    stickPosX1 = calculateStickPosition1X();
    stickPosY1 = calculateStickPosition1Y();
}

/* system backlight */
void Systems::backlightControl(bool state)
{
    pinMode(PIN_BACKLIGHT_LCD, OUTPUT);

    if (state == true)
    {
        digitalWrite(PIN_BACKLIGHT_LCD, 1); // on
    }
    else
    {
        digitalWrite(PIN_BACKLIGHT_LCD, 0); // off
    }
}

/* oblect - obj0y, obj1y */
int8_t Systems::countingObjectStickPosition0Y() // obj 0y
{
    RAW_DATA_Y0 = analogRead(PIN_STICK_0Y);

    if ((RAW_DATA_Y0 < (DEF_RES_Y0 - 200)) && (RAW_DATA_Y0 > (DEF_RES_Y0 - 1100)))
    {
        return OBJ_Y0 = OBJ_Y0 - 1;
    }
    else if (RAW_DATA_Y0 < (DEF_RES_Y0 - 1100))
    {
        return OBJ_Y0 = OBJ_Y0 - 1; // 2
    }
    else if ((RAW_DATA_Y0 > (DEF_RES_Y0 + 200)) && (RAW_DATA_Y0 < (DEF_RES_Y0 + 1100)))
    {
        return OBJ_Y0 = OBJ_Y0 + 1;
    }
    else if (RAW_DATA_Y0 > (DEF_RES_Y0 + 1100))
    {
        return OBJ_Y0 = OBJ_Y0 + 1; // 2
    }
    else
        return OBJ_Y0 = 0;
}

int8_t Systems::countingObjectStickPosition1Y() // obj 1y
{
    RAW_DATA_Y1 = analogRead(PIN_STICK_1Y);

    if ((RAW_DATA_Y1 < (DEF_RES_Y1 - 200)) && (RAW_DATA_Y1 > (DEF_RES_Y1 - 1100)))
    {
        return OBJ_Y1 = OBJ_Y1 - 1;
    }
    else if (RAW_DATA_Y1 < (DEF_RES_Y1 - 1100))
    {
        return OBJ_Y1 = OBJ_Y1 - 1; // 2
    }
    else if ((RAW_DATA_Y1 > (DEF_RES_Y1 + 200)) && (RAW_DATA_Y1 < (DEF_RES_Y1 + 1100)))
    {
        return OBJ_Y1 = OBJ_Y1 + 1;
    }
    else if (RAW_DATA_Y1 > (DEF_RES_Y1 + 1100))
    {
        return OBJ_Y1 = OBJ_Y1 + 1; // 2
    }
    else
        return OBJ_Y1 = 0;
}

int8_t Systems::countingObjectStickPosition0X()
{
    return 0;
}

int8_t Systems::countingObjectStickPosition1X()
{
    return 0;
}

/* timer */
void Timer::timer(void (*f)(void), int interval)
{
    unsigned long currTime = millis();
    if (currTime - prevTime >= interval)
    {
        prevTime = currTime;
        f();
    }
}