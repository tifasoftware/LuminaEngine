#pragma once
#include "IControllable.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class Controller {
    public:
    Controller();
    void Possess(IControllable* p);
    void QueuePawn(IControllable* p);
    void SendInput();
    void Release();

    private:
    IControllable* pawn;
    IControllable* queued_pawn;
    SDL_Event event;
    void PSP_ProcessInput();
    void PC_ProcessInput();
};
