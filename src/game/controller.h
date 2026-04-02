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

    FILE* debugLog;
    void DebugLog(const char* fmt, ...);
};
