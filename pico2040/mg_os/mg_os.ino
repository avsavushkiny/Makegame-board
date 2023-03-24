/*
  makegame OS / beta / 191222
  update 090323
*/

/* include */
#include "sys.h"          //sticks
#include "sys_gfx.h"      //lcd
#include "sys_xbmp.h"     //bitmap
#include "sys_logo.h"     //start page - logotype
#include "sys_trm.h"      //terminal

/* global variable */
void renderHelloWorld(); void printHelloWorld(); void renderMyPong();
void calcMyPong();

user::Project myFirstProject {1, renderHelloWorld, "Hello World", false};
user::Project myPong {2, renderMyPong, "Pong\nAtari 1972", false};

/* initial setting */
void setup()
{
  mg::initialization();
  mg::greetings();
  mg::terminal();
}

/* entry point */
void loop()
{
  //myFirstProject.function();
  myPong.function();
}

void renderHelloWorld()
{
  gfx.render(printHelloWorld, 0);
}

void printHelloWorld()
{
  gfx.print(myFirstProject.discription, 0, 10, 10, 6);
}

void renderMyPong()
{
  gfx.render(calcMyPong, 0);
}

void calcMyPong()
{
    //defGame::drawLogo();
    defGame::drawField();
    defGame::drawRacket();
    defGame::calculateMovementRackets();
    defGame::drawBall();
    defGame::calculateMovementBall();
    defGame::drawScore();

    gfx.print(myPong.discription, 39, 53, 9, 5);
}