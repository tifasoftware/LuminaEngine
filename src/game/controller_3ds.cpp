#include <platform/platform.h>
#include <platform/universalsdl.h>

#include "controller.h"

#if defined(PLATFORM_3DS) || defined(LIB_SDL1)
#include <3ds.h>

void Controller::N3DS_ProcessInput() {
    hidScanInput();

    uint32_t kDown = hidKeysDown();
    uint32_t kHeld = hidKeysHeld();
    uint32_t kUp = hidKeysUp();

    if (kDown && KEY_START) {
        pawn->OnButtonStart();
    } else if (kDown && KEY_SELECT) {
        pawn->OnButtonSelect();
    } else if (kDown && KEY_UP) {
        pawn->OnButtonUp();
        pawn->OnMoveUp();
    } else if (kDown && KEY_DOWN) {
        pawn->OnButtonDown();
        pawn->OnMoveDown();
    } else if (kDown && KEY_LEFT) {
        pawn->OnButtonLeft();
        pawn->OnMoveLeft();
    } else if (kDown && KEY_RIGHT) {
        pawn->OnButtonRight();
        pawn->OnMoveRight();
    } else if (kUp && KEY_UP) {
        pawn->OnStopMoveUp();
    } else if (kUp && KEY_DOWN) {
        pawn->OnStopMoveDown();
    } else if (kUp && KEY_LEFT) {
        pawn->OnStopMoveLeft();
    } else if (kUp && KEY_RIGHT) {
        pawn->OnStopMoveRight();
    } else if (kDown && KEY_A) {
        pawn->OnButtonA();
    } else if (kDown && KEY_B) {
        pawn->OnButtonB();
    } else if (kDown && KEY_X) {
        pawn->OnButtonX();
    } else if (kDown && KEY_Y) {
        pawn->OnButtonY();
    }
}
#else

void N3DS_ProcessInput() {
    //no-ops
}

#endif