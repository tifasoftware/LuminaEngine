#include "controller.h"
#include <platform/platform.h>

Controller::Controller() {
    pawn = nullptr;
}

void Controller::Possess(IControllable *p) {
    if (p != nullptr) pawn = p;
}

void Controller::Release() {
    pawn = nullptr;
}

void Controller::SendInput() {
    if (pawn != nullptr) {
        #ifdef PLATFORM_PSP
        PSP_ProcessInput();
        #endif
        #ifdef PLATFORM_PC
        PC_ProcessInput();
        #endif
    }
}
