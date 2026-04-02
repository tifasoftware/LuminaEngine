#include "controller.h"
#include <platform/platform.h>

Controller::Controller() {
    pawn = nullptr;
    queued_pawn = nullptr;

    debugLog = nullptr;
    //debugLog = fopen("sdmc:/debug.txt", "w");
}

void Controller::Possess(IControllable *p) {
    pawn = p;
    pawn->activate();
}

void Controller::QueuePawn(IControllable *p) {
    queued_pawn = p;
}

void Controller::Release() {
    pawn = nullptr;
}

void Controller::SendInput() {
    if (pawn != nullptr && pawn->getActive()) {
        #ifdef PLATFORM_PSP
        PSP_ProcessInput();
        #endif
    #ifdef PLATFORM_3DS
        N3DS_ProcessInput();
    #endif
        #ifdef PLATFORM_PC
        PC_ProcessInput();
        #endif
    } else {
        if (queued_pawn != nullptr) {
            pawn = queued_pawn;
            queued_pawn = nullptr;
            SendInput();
        }
    }
}

void Controller::DebugLog(const char* fmt, ...) {
    if (!debugLog) return;

    va_list args;
    va_start(args, fmt);
    vfprintf(debugLog, fmt, args);
    va_end(args);
    fflush(debugLog);  // Important!
}
