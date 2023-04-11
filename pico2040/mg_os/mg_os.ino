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

/* prototype */
void renderHelloWorld(); void printHelloWorld(); void renderMyPong();
void calcMyPong(); void calcFollowTheLink(); void renderFollowTheLink();

user::Project myFirstProject {1, renderHelloWorld, "Hello World", false};
user::Project myPong {2, renderMyPong, "Pong\nAtari 1972", false};
user::Project followTheLink {3, renderFollowTheLink, "Follow the link", false};

/* add object timer */
Timer timer_0;

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
  //myPong.function();
  followTheLink.function();
}

void renderFollowTheLink()
{
  gfx.render(calcFollowTheLink, 0);
}

void calcFollowTheLink()
{
  u8g2.drawXBMP(5, 15, qr_w, qr_w, qr_bits);
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
    timer_0.timer(defGame::calculateMovementBall, 0);
    defGame::drawScore();

    gfx.print(myPong.discription, 39, 53, 9, 5);
}