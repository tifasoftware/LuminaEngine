#include <platform/platform.h>
#include <platform/universalsdl.h>

#include "controller.h"

#if defined(PLATFORM_3DS) && defined(LIB_SDL1)
#include <3ds.h>

static const int BTN_A = 1;
static const int BTN_B = 2;
static const int BTN_X = 3;
static const int BTN_Y = 4;
static const int BTN_START = 0;
static const int BTN_SELECT = 7;

void Controller::N3DS_ProcessInput() {
    SDL_JoystickUpdate();

    for (int i = 0; i < 10; i++) {
        Uint8 cur = SDL_JoystickGetButton(joystick, i);
        Uint8 prev = prevButtons[i];

        if (cur && !prev) {
            // Just pressed this frame
            if (i == BTN_START)  pawn->OnButtonStart();
            if (i == BTN_SELECT) pawn->OnButtonSelect();
            if (i == BTN_A)      pawn->OnButtonA();
            if (i == BTN_B)      pawn->OnButtonB();
            if (i == BTN_X)      pawn->OnButtonX();
            if (i == BTN_Y)      pawn->OnButtonY();
        }

        prevButtons[i] = cur;
    }

    u32 held = hidKeysHeld();

    Uint8 curDpad[4] = {
        (held & 64) ? 1 : 0,
        (held & 128) ? 1 : 0,
        (held & 32) ? 1 : 0,
        (held & 16) ? 1 : 0,
    };

    if (curDpad[N3DS_UP] && !prevDpad[N3DS_UP]) {
        pawn->OnButtonUp();
        pawn->OnMoveUp();
    }

    if (curDpad[N3DS_DOWN] && !prevDpad[N3DS_DOWN]) {
        pawn->OnButtonDown();
        pawn->OnMoveDown();
    }

    if (curDpad[N3DS_LEFT] && !prevDpad[N3DS_LEFT]) {
        pawn->OnButtonLeft();
        pawn->OnMoveLeft();
    }

    if (curDpad[N3DS_RIGHT] && !prevDpad[N3DS_RIGHT]) {
        pawn->OnButtonRight();
        pawn->OnMoveRight();
    }

    if (!curDpad[N3DS_UP] && prevDpad[N3DS_UP]) pawn->OnStopMoveUp();
    if (!curDpad[N3DS_DOWN] && prevDpad[N3DS_DOWN]) pawn->OnStopMoveDown();
    if (!curDpad[N3DS_LEFT] && prevDpad[N3DS_LEFT]) pawn->OnStopMoveLeft();
    if (!curDpad[N3DS_RIGHT] && prevDpad[N3DS_RIGHT]) pawn->OnStopMoveRight();

    prevDpad[N3DS_UP] = curDpad[N3DS_UP];
    prevDpad[N3DS_DOWN] = curDpad[N3DS_DOWN];
    prevDpad[N3DS_LEFT] = curDpad[N3DS_LEFT];
    prevDpad[N3DS_RIGHT] = curDpad[N3DS_RIGHT];

    // Still keep the event loop to prevent the queue from filling up
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) pawn->OnQuit();
    }
}
#else

void N3DS_ProcessInput() {
    //no-ops
}

#endif