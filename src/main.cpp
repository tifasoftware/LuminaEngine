#include <SDL.h>
#include <SDL_image.h>
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
    FILE* f = fopen("/tmp/lumina.log", "w");
    fprintf(f, "main started\n");
    fprintf(f, "argv[0]: %s\n", argv[0]);
    fclose(f);

    auto gp = new GamePlay();

    while (gp->gameRunning()) { 
        gp->GameLoop();
    }
    gp->Exit();

    return 0;
}


