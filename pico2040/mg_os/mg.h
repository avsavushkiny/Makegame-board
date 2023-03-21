/*
  mg
*/
#pragma once

#include "sys.h"          //sticks
#include "sys_gfx.h"      //lcd
#include "sys_xbmp.h"     //bitmap
#include "sys_logo.h"     //start page - logotype
#include "sys_trm.h"      //terminal

namespace mg
{
    /* initial settings */
    int initialization()
    {
        gfx.screen();
        analogReadResolution(12);
        return 0;
    }

    /* start greeting */
    int greetings()
    {
        systemsLogo();
        return 0;
    }

    /* start command-line-interface terminal */
    int terminal()
    {
        terminal();
        return 0;
    }

    /* user-object to run */
    struct Use
    {
        const int number;
        void (*myFunction)();
        const char *discription;
        bool active;
    };
}
