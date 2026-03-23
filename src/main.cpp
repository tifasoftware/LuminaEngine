#include <SDL.h>
#include <SDL_image.h>
#ifdef PLATFORM_PSP
#include <pspkernel.h>
#include <pspdisplay.h>
#endif
#include "lumina.h"



int main(int argc, char *argv[])
{
    auto gp = new GamePlay();

    while (gp->gameRunning()) { 
        gp->GameLoop();
    }
    gp->Exit();

    return 0;
}


