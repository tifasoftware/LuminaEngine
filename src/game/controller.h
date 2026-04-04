#pragma once
#include "IControllable.h"
#include <platform/platform.h>
#include <platform/universalsdl.h>

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
    void N3DS_ProcessInput();

#ifdef LIB_SDL1
    SDL_Joystick* joystick;
    Uint8 prevButtons[10] = {0};
    Uint8 prevDpad[4] = {0};

    static const int N3DS_UP = 0;
    static const int N3DS_DOWN = 1;
    static const int N3DS_LEFT = 2;
    static const int N3DS_RIGHT = 3;
#endif
};
