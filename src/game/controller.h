#pragma once
#include "IControllable.h"
#include <platform/platform.h>
#include <platform/universalsdl.h>

#if defined(PLATFORM_ANDROID) || (defined(PLATFORM_PC) && defined(USER_LIGHTNING))
#include "vgui/mobile/os_controls.h"
#endif

class Controller {
    public:
    Controller();
    ~Controller();
    void Possess(IControllable* p);
    void QueuePawn(IControllable* p);
    void SendInput();
    void Release();

#if defined(PLATFORM_ANDROID) || (defined(PLATFORM_PC) && defined(USER_LIGHTNING))
    void ConnectOSC(OnScreenControls* o, int sW, int sH) { this->osc = o; screen_height = sH; screen_width = sW; }
#endif

    private:
    IControllable* pawn;
    IControllable* queued_pawn;
    SDL_Event event;
    void PSP_ProcessInput();
    void PC_ProcessInput();
    void N3DS_ProcessInput();

    void Mobile_ProcessInput();
    void OSC_SendInput();

    bool upDownController = false;
    bool leftRightController = false;

    int GetControllerCount() { return SDL_NumJoysticks(); }

#if defined(PLATFORM_ANDROID) || (defined(PLATFORM_PC) && defined(USER_LIGHTNING))
    OnScreenControls* osc;
    int screen_width = 480;
    int screen_height = 272;
#endif



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
