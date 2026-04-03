#include <platform/platform.h>
#include <platform/universalsdl.h>

#include "controller.h"

#if defined(PLATFORM_3DS) || defined(LIB_SDL1)
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

        pawn->OnButtonPress(cur);

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

    Uint8 hat = SDL_JoystickGetHat(joystick, 0);


    if (hat & 1) {
        pawn->OnMoveUp();
    } else if (hat & 4) {
        pawn->OnMoveDown();
    } else {
        //pawn->OnStopMoveDown();
    }
    if (hat & 8) {
        pawn->OnMoveLeft();
    } else if (hat & 2) {
        pawn->OnMoveRight();
    } else {
        //pawn->OnStopMoveRight();
    }

    prevHat = hat;

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