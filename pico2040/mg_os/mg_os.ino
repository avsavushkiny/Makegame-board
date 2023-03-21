/*
  makegame OS / beta / 191222
  update 090323
*/

/* include */
#include "mg.h"           //mg
#include "sys.h"          //sticks
#include "sys_gfx.h"      //lcd
#include "sys_xbmp.h"     //bitmap
#include "sys_logo.h"     //start page - logotype
#include "sys_trm.h"      //terminal

/* global variable */
void renderHelloWorld(); void printHelloWorld();

mg::Use myFirstProject {1, renderHelloWorld, "Hello World", false};

/* initial setting */
void setup()
{
  mg::initialization();
  mg::greetings();
}

/* entry point */
void loop()
{
  myFirstProject.function();
}

void renderHelloWorld()
{
  gfx.render(printHelloWorld, 0);
}

void printHelloWorld()
{
  gfx.print(myFirstProject.discription, 0, 10, 10, 6);
}