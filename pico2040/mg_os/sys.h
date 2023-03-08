/*
    coordinate calculation, buttons, backlight
*/

#pragma once
#include <Arduino.h>

class Systems
{
  private:
    int DEF_RES_Y0 = 2100;
    int DEF_RES_Y1 = 2100;
    int DEF_RES_X0 = 2100;
    int DEF_RES_X1 = 2100;

    int CORR_y0 = 100;

    int JOI_0Y = 27;
    int JOI_1Y = 28;
    int JOI_X0 = 26;
    int JOI_X1 = 26;

    int H_RES = 64;
    int W_RES = 128;

    int yJoi0 = H_RES / 2;
    int yJoi1 = H_RES / 2;
    int xJoi0 = W_RES / 2;
    int xJoi1 = W_RES / 2;

    int objUD0y{};
    int objUD1y{};
    int objUD0x{};

    int dataJoiY0{};
    int dataJoiY1{};
    int dataJoiX0{};
    int dataJoiX1{};

    unsigned long prevTime_0{}, prevTime_1{}, prevTime_2{}, prevTime_3{};

  public:
    /* systems button / sw0, sw1 */
    bool sw0()
    {
      if (digitalRead(6) == false)
      {
        return true;
      }
      else return false;
    }

    bool sw1()
    {
      if (digitalRead(7) == false)
      {
        return true;
      }
      else return false;
    }

    /* interrupts 11*/
    bool iSw()
    {
      if (digitalRead(7) == false)
      {
        if ((digitalRead(6) == false) && (digitalRead(7) == false))
        {
          return true;
        }
        else return false;
      }
      else return false;
    }

    /* system dADC / joi0y, joi1y, joi0x */
    int joi0y()
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

    int joi1y()
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

    int joi0x()
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

    /* system backlight */
    void backlight(bool state)
    {
      pinMode(8, OUTPUT);

      if (state == true)
      {
        digitalWrite(8, 1);
      }
      else
      {
        digitalWrite(8, 0);
      }
    }

    /* oblect - obj0y, obj1y */
    int obj0y()
    {
      dataJoiY0 = analogRead(JOI_0Y);

      if ((dataJoiY0 < (DEF_RES_Y0 - 200)) && (dataJoiY0 > (DEF_RES_Y0 - 1100)))
      {
        return objUD0y = objUD0y - 1;
      }
      else if (dataJoiY0 < (DEF_RES_Y0 - 1100))
      {
        return objUD0y = objUD0y - 1; //2
      }
      else if ((dataJoiY0 > (DEF_RES_Y0 + 200)) && (dataJoiY0 < (DEF_RES_Y0 + 1100)))
      {
        return objUD0y = objUD0y + 1;
      }
      else if (dataJoiY0 > (DEF_RES_Y0 + 1100))
      {
        return objUD0y = objUD0y + 1; //2
      }
      else
        return objUD0y = 0;
    }

    int obj1y()
    {
      dataJoiY1 = analogRead(JOI_1Y);

      if ((dataJoiY1 < (DEF_RES_Y1 - 200)) && (dataJoiY1 > (DEF_RES_Y1 - 1100)))
      {
        return objUD1y = objUD1y - 1;
      }
      else if (dataJoiY1 < (DEF_RES_Y1 - 1100))
      {
        return objUD1y = objUD1y - 1; //2
      }
      else if ((dataJoiY1 > (DEF_RES_Y1 + 200)) && (dataJoiY1 < (DEF_RES_Y1 + 1100)))
      {
        return objUD1y = objUD1y + 1;
      }
      else if (dataJoiY1 > (DEF_RES_Y1 + 1100))
      {
        return objUD1y = objUD1y + 1; //2
      }
      else
        return objUD1y = 0;
    }

    /* timer */
    bool timer_0(void(*timer_fn)(void), int interval)
    {
      unsigned long currTime = millis();
      if (currTime - prevTime_0 >= interval)
      {
        prevTime_0 = currTime; return 0;
      }
      else
      {
        timer_fn(); return 1;
      }
    }

    bool timer_1(void(*timer_fn)(void), int interval)
    {
      unsigned long currTime = millis();
      if (currTime - prevTime_1 >= interval)
      {
        prevTime_1 = currTime; return 0;
      }
      else
      {
        timer_fn(); return 1;
      }
    }

    void debug(String text, int  data_0, int data_1)
    {
      String outputData = text + " " + data_0 + " " + data_1;
      Serial.println(outputData);
    }
};

Systems sys;

//add data exceptions by stick
