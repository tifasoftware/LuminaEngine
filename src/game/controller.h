#pragma once
#include "IControllable.h"
#include <SDL.h>
#include <SDL_image.h>

class Controller {
    public:
    Controller();
    void Possess(IControllable* p);
    void SendInput();
    void Release();

    private:
    IControllable* pawn;
    SDL_Event event;
    void PSP_ProcessInput();
    void PC_ProcessInput();
};
