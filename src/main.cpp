#include <SDL.h>
#include <SDL_image.h>
#include <pspkernel.h>
#include <pspdisplay.h>
#include "lumina.h"



int main(int argc, char *argv[])
{
    GamePlay* gp = new GamePlay();

    while (gp->gameRunning()) { 
        gp->GameLoop();
    }
    gp->Exit();

    return 0;
}


