/*
  terminal
*/

#pragma once

#include "sys.h"
#include "mg.h"
#include "sys_gfx.h"
#include "sys_xbmp.h"
#include "sys_logo.h"

/* prototype */
void clearCommandTerminal();

/* command type */
struct Command
{
  char const *text;
  void (*f)();
  bool active;
};

/* data entered by the user */
String trmUserData = "com";

/* terminal interface */
void headerTerminal()
{
  //u8g2.drawXBMP(0, 2, trm_l_w, trm_l_h, trm_l);
  gfx.winkPrint(printf, "-" /* identifier */ + trmUserData, 0, 10, 500);
}

/* standard commands */
namespace defCommand
{
  /* microcontroller information */
  void infoSystems()
  {
    gfx.print("Raspberry Pico 2040\nDual ARM Cortex-M0+\nCPU speed - 133 MHz\nFlash - 2 MB\nSRAM - 264 KB", 0, 20, 10, 6);
  }

  /* graphics chip information */
  void infoGfx()
  {
    gfx.print("Chip - ST7565\nRes - 128x64\nVersion - White", 0, 20, 10, 6);
  }

  /* information about the analog-to-digital converter */
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
}

/* commands for standard game */
namespace defGame
{
  /* prototype defGame */
  void addEffectBall(int paddleSpeed);
  
  /* def visuals */
  #define SCREEN_OX 0
  #define SCREEN_OY 0
  #define SCREEN_WIDTH 127
  #define SCREEN_HEIGHT 63
  #define PADDLE_WIDTH 4
  #define PADDLE_HEIGHT 10
  #define PADDLE_PADDING 10
  #define BALL_SIZE 3
  #define SCORE_PADDING 10

  #define EFFECT_SPEED 0.5
  #define MIN_Y_SPEED 0.5
  #define MAX_Y_SPEED 2

  /* state effect ball */
  byte stateEffectBall = false;

  /* def value */
  float ballX = SCREEN_WIDTH / 2;
  float ballY = SCREEN_HEIGHT / 2;
  float ballSpeedX = 2;
  float ballSpeedY = 1;

  int paddleLocationA = 0;
  int paddleLocationB = 0;
  int lastPaddleLocationA = 0;
  int lastPaddleLocationB = 0;

  int scoreA = 0;
  int scoreB = 0;

  /* display and calculation functions */
  /* draw the playing field */
  void drawField()
  {
    // draw central line
    for (int i = 1; i < SCREEN_HEIGHT; i += 4)
    {
      u8g2.drawVLine(SCREEN_WIDTH / 2, i, 2); // x, y, length
    }
    // draw field line
    u8g2.drawHLine(SCREEN_OX, SCREEN_OY, SCREEN_WIDTH);     // x, y, length
    u8g2.drawHLine(SCREEN_OX, SCREEN_HEIGHT, SCREEN_WIDTH); // x, y, length
  }

  /* draw players rackets */
  void drawRacket()
  {
    // draw paddle A
    u8g2.drawFrame(PADDLE_PADDING, paddleLocationA, PADDLE_WIDTH, PADDLE_HEIGHT); // x, y, w, h
    // draw paddle B
    u8g2.drawFrame(SCREEN_WIDTH - PADDLE_WIDTH - PADDLE_PADDING, paddleLocationB, PADDLE_WIDTH, PADDLE_HEIGHT); // x, y, w, h
  }
  
  /* draw a ball */
  void drawBall()
  {
    // draw ball
    u8g2.drawFrame(ballX, ballY, BALL_SIZE, BALL_SIZE); // x, y, w, h
  }

  /* draw a scoreboard */
  void drawScore()
  {
    // print scores
    u8g2.setColorIndex(1);           // black
    u8g2.setFont(u8g2_font_6x10_tr); // w 5px, h 9px, use https://github.com/olikraus/u8glib/wiki/fontgroup
    u8g2.setCursor(15, 10);          // x, y
    u8g2.print(scoreA);              // var scoreA
    u8g2.setCursor(78, 10);          // x, y
    u8g2.print(scoreB);              // var scoreB
  }

  /* draw the logo of the game */
  void drawLogo()
  {
    //pong_log.XBM
    const uint8_t pongLogo[] PROGMEM=
    {
      //w 70px, h 20px
      0x00, 0x00, 0x00, 0x06, 0x00, 0x60, 0x00, 0x00, 0x00, 0xFE, 0x03, 0xE0, 
      0x7F, 0x00, 0xFC, 0x03, 0xE0, 0x1F, 0xFE, 0x0F, 0xF0, 0xFF, 0x01, 0xFE, 
      0x07, 0xF0, 0x1F, 0xFE, 0x0F, 0xF8, 0xFF, 0x03, 0xFF, 0x0F, 0xFC, 0x1F, 
      0x1E, 0x1E, 0x7C, 0xE0, 0x03, 0x0F, 0x0F, 0xFC, 0x19, 0x1E, 0x1E, 0x3E, 
      0xC0, 0x87, 0x07, 0x1E, 0x3E, 0x00, 0x1E, 0x1C, 0x1E, 0x80, 0x8F, 0x07, 
      0x1E, 0x1F, 0x00, 0x1E, 0x1E, 0x0F, 0x00, 0x8F, 0x07, 0x1E, 0x0F, 0x00, 
      0x1E, 0x1F, 0x0F, 0x00, 0x8F, 0x07, 0x1E, 0x0F, 0x00, 0xFE, 0x0F, 0x0F, 
      0x00, 0x8F, 0x07, 0x1E, 0x0F, 0x00, 0xFE, 0x07, 0x0F, 0x00, 0x8F, 0x07, 
      0x1E, 0x8F, 0x1F, 0xFE, 0x03, 0x0F, 0x00, 0x8F, 0x07, 0x1E, 0x8F, 0x1F, 
      0x1E, 0x00, 0x1E, 0x00, 0x8F, 0x07, 0x1E, 0x8F, 0x1F, 0x1E, 0x00, 0x1E, 
      0x80, 0x87, 0x07, 0x1E, 0x1F, 0x1E, 0x1E, 0x00, 0x7E, 0xC0, 0x87, 0x07, 
      0x1E, 0x3E, 0x1E, 0x1E, 0x00, 0xFC, 0xF9, 0x83, 0x07, 0x1E, 0x7C, 0x1E, 
      0x1E, 0x00, 0xF8, 0xFF, 0x81, 0x07, 0x1E, 0xFC, 0x1F, 0x1E, 0x00, 0xE0, 
      0xFF, 0x80, 0x07, 0x1E, 0xF0, 0x1F, 0x1E, 0x00, 0x80, 0x3F, 0x80, 0x07, 
      0x1E, 0xE0, 0x1F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    };

    u8g2.drawXBMP(29, 16, 70, 20, pongLogo); // x, y, w, h, xbmp

    // gfx.print("Atari. 1972\nGame for two", 30, 43);

    u8g2.setFont(u8g2_font_6x10_tr);
    u8g2.setCursor(30, 43); // x, y
    u8g2.print((String) "Atari 1972");
    u8g2.setCursor(30, 50); // x, y
    u8g2.print((String) "Game for two");

    // delay(2000);
  }

  void calculateMovementRackets()
  {
    paddleLocationA = sys.joi0y();
    paddleLocationB = sys.joi1y();
  }

  void calculateMovementBall()
  {
    ballX += ballSpeedX;
    ballY += ballSpeedY;

    int paddleSpeedA = paddleLocationA - lastPaddleLocationA;
    int paddleSpeedB = paddleLocationB - lastPaddleLocationB;

    //bounce from top and bottom
    if (ballY >= SCREEN_HEIGHT - BALL_SIZE || ballY <= 0)
    {
      ballSpeedY *= -1;
    }

    //bounce from paddle A
    if (ballX >= PADDLE_PADDING && ballX <= PADDLE_PADDING + BALL_SIZE && ballSpeedX < 0)
    {
      if (ballY > paddleLocationA - BALL_SIZE && ballY < paddleLocationA + PADDLE_HEIGHT)
      {
        ballSpeedX *= -1;

        addEffectBall(paddleSpeedA);
      }
    }

    //bounce from paddle B
    if (ballX >= SCREEN_WIDTH - PADDLE_WIDTH - PADDLE_PADDING - BALL_SIZE && ballX <= SCREEN_WIDTH - PADDLE_PADDING - BALL_SIZE && ballSpeedX > 0)
    {
      if (ballY > paddleLocationB - BALL_SIZE && ballY < paddleLocationB + PADDLE_HEIGHT)
      {
        ballSpeedX *= -1;

        addEffectBall(paddleSpeedB);
      }
    }

    //score points if ball hits wall behind paddle
    if (ballX >= SCREEN_WIDTH - BALL_SIZE || ballX <= 0)
    {
      if (ballSpeedX > 0)
      {
        scoreA++;
        ballX = SCREEN_WIDTH / 4;
      }
      if (ballSpeedX < 0)
      {
        scoreB++;
        ballX = SCREEN_WIDTH / 4 * 3;
      }
    }

    //set last paddle locations
    lastPaddleLocationA = paddleLocationA;
    lastPaddleLocationB = paddleLocationB;
    }

  //effect
  void addEffectBall(int paddleSpeed)
  {
    float oldBallSpeedY = ballSpeedY;

    //add effect to ball when paddle is moving while bouncing
    //for every pixel of paddle movement, add or substact EFFECT_SPEED to ballspeed
    for (int effect = 0; effect < abs(paddleSpeed); effect++)
    {
      if (paddleSpeed > 0)
      {
        ballSpeedY += EFFECT_SPEED;
      }
      else
      {
        ballSpeedY -= EFFECT_SPEED;
      }
    }

    //limit to minimum speed
    if (ballSpeedY < MIN_Y_SPEED && ballSpeedY > -MIN_Y_SPEED)
    {
      if (ballSpeedY > 0)
        ballSpeedY = MIN_Y_SPEED;
      if (ballSpeedY < 0)
        ballSpeedY = -MIN_Y_SPEED;
      if (ballSpeedY == 0)
        ballSpeedY = oldBallSpeedY;
    }

    //limit to maximum speed
    if (ballSpeedY > MAX_Y_SPEED)
      ballSpeedY = MAX_Y_SPEED;
    if (ballSpeedY < -MAX_Y_SPEED)
      ballSpeedY = -MAX_Y_SPEED;
  }
}

/* enumeration of objects - commands */
Command commands[]
{
    {"system", defCommand::infoSystems, false},
    {"graphc", defCommand::infoGfx, false},
    {"sticks", defCommand::infoAdc, false},
    {"clrcom", clearCommandTerminal, false},
    {"drwfld", defGame::drawField, false},
    {"drwrac", defGame::drawRacket, false},
    {"drwbal", defGame::drawBall, false},
    {"drwscr", defGame::drawScore, false},
    {"drwlog", defGame::drawLogo, false},
    {"clcrac", defGame::calculateMovementRackets, false},
    {"clcbal", defGame::calculateMovementBall, false},
    {"user", &mg::user, false}
};

/* delete all commands */
void clearCommandTerminal()
{
  for (Command &command : commands)
  {
    command.active = false;
  }
}

/* command stack */
void calcTerminal()
{
  headerTerminal();

  for (Command &command : commands)
  {
    if (command.active)
    {
      command.f();
    }
  }
}

/* pushing data onto the stack */
void terminal()
{
  gfx.render(calcTerminal, 0);

  if (not Serial.available())
  {
    return;
  }

  char text[10]{};
  Serial.readBytesUntil('\n', text, sizeof(text));
  trmUserData = text;

  for (Command &command : commands)
  {
    if (not strncmp(command.text, text, 6))
    {
      command.active = true;
    }
    // else
    // command.active = false;
  }
}
