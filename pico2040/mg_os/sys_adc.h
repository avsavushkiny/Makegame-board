/*
  test ADC page
*/

#pragma once

#include <U8g2lib.h>
#include "sys.h"
#include "sys_gfx.h"

void infoAdc();

void infoAdc()
{
  if (sys.sw0() == true)
  {
    u8g2.drawBox(sys.joi0x(), sys.joi0y(), 10, 10);
  }
  else
  {
    u8g2.drawFrame(sys.joi0x(), sys.joi0y(), 10, 10);
  }

  if (sys.sw1() == true)
  {
    u8g2.drawBox(sys.joi0x(), sys.joi1y(), 25, 25);
  }
  else
  {
    u8g2.drawFrame(sys.joi0x(), sys.joi1y(), 25, 25);
  }
}