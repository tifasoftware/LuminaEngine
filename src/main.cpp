#include <platform/platform.h>
#include <platform/universalsdl.h>
#include <string>
#ifdef PLATFORM_PSP
#include <pspkernel.h>
#include <pspdisplay.h>
#endif
#include "lumina.h"

#ifdef PLATFORM_OSX
#include <unistd.h>
#include <limits.h>
#endif

#ifdef PLATFORM_3DS
#include <3ds.h>
#endif



int main(int argc, char *argv[])
{
    auto gp = new GamePlay();

#ifdef PLATFORM_3DS
    aptSetSleepAllowed(true);

    while (gp->gameRunning() && aptMainLoop()) {
        if (aptShouldClose())
            break;

        if (!aptIsActive()) {
            // suspended by HOME menu, just wait
            gspWaitForVBlank();
            continue;
        }

        gp->GameLoop();
    }
#else
    while (gp->gameRunning()) {
        gp->GameLoop();
    }
#endif
    gp->Exit();

    return 0;
}


