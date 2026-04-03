#include <platform/platform.h>
#include <platform/universalsdl.h>

#include "controller.h"

#if defined(PLATFORM_3DS) && defined(LIB_SDL1)
#include <3ds.h>

void Controller::N3DS_ProcessInput() {
    hidScanInput();
    u32 kDown = hidKeysDown();
    u32 kHeld = hidKeysHeld();
    u32 kUp = hidKeysUp();

    if (kDown) DebugLog("kDown: %08lX\n", kDown);
    if (kHeld) DebugLog("kHeld: %08lX\n", kHeld);
    if (kUp) DebugLog("kUp: %08lX\n", kUp);

    // Button PRESS events (one-time actions)
    if (kDown & KEY_START) {
        pawn->OnButtonStart();
    }
    if (kDown & KEY_SELECT) {
        pawn->OnButtonSelect();
    }
    if (kDown & KEY_DUP) {
        pawn->OnButtonUp();
    }
    if (kDown & KEY_DDOWN) {
        pawn->OnButtonDown();
    }
    if (kDown & KEY_DLEFT) {
        pawn->OnButtonLeft();
    }
    if (kDown & KEY_DRIGHT) {
        pawn->OnButtonRight();
    }
    if (kDown & KEY_A) {
        pawn->OnButtonA();
    }
    if (kDown & KEY_B) {
        pawn->OnButtonB();
    }
    if (kDown & KEY_X) {
        pawn->OnMoveUp();
        pawn->OnButtonX();
    }
    if (kDown & KEY_Y) {
        pawn->OnButtonY();
        pawn->OnMoveDown();
    }

    // HELD state (continuous movement - called every frame)
    if (kDown & KEY_DUP) {
        pawn->OnMoveUp();
    }
    if (kDown & KEY_DDOWN) {
        pawn->OnMoveDown();
    }
    if (kDown & KEY_DLEFT) {
        pawn->OnMoveLeft();
    }
    if (kDown & KEY_DRIGHT) {
        pawn->OnMoveRight();
    }
}
#else

void N3DS_ProcessInput() {
    //no-ops
}

#endif