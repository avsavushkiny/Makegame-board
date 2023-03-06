/*
    exceptions
*/

#pragma once
#include <Arduino.h>

enum STATE_OS
{
  SYS_OK,
  SYS_ERROR,
} stateOs;

class Exceptions
{
  private:
  public:

} exc;

/* func */
void messageOs()
{
  u8g2.setFont(u8g2_font_6x10_tr);

  String title_1 = "Error. No procces";

  if (stateOs == SYS_ERROR)
  {
  u8g2.setCursor(6, 27);
  u8g2.print(title_1); 
  }

  delay(5000);
  stateOs = SYS_OK;
}