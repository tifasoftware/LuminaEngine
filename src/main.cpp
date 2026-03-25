#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
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



int main(int argc, char *argv[])
{
    auto gp = new GamePlay();

    while (gp->gameRunning()) { 
        gp->GameLoop();
    }
    gp->Exit();

    return 0;
}


