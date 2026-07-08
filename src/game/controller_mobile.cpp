#include <platform/platform.h>
#include <platform/universalsdl.h>

#include "controller.h"

#if defined(LIB_SDL2) && ( defined(PLATFORM_ANDROID) || defined(PLATFORM_PC) )
void Controller::Mobile_ProcessInput() {
    if (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                pawn->OnQuit();
                break;
            case SDL_CONTROLLERDEVICEADDED:
                // Connect a controller when it is connected
                SDL_GameControllerOpen(event.cdevice.which);
                break;
            case SDL_CONTROLLERDEVICEREMOVED:
                // Vice-versa for when it's disconnected
                //SDL_GameControllerClose(event.cdevice.which);
                break;
            case SDL_CONTROLLERBUTTONDOWN:
                if(event.cbutton.button == SDL_CONTROLLER_BUTTON_START) {
                    pawn->OnButtonStart();
                } else if (event.cbutton.button == SDL_CONTROLLER_BUTTON_BACK) {
                    pawn->OnButtonSelect();
                } else if (event.cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_UP) {
                    pawn->OnMoveUp();
                    pawn->OnButtonUp();
                } else if (event.cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_DOWN) {
                    pawn->OnMoveDown();
                    pawn->OnButtonDown();
                } else if (event.cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_LEFT) {
                    pawn->OnMoveLeft();
                    pawn->OnButtonLeft();
                } else if (event.cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_RIGHT) {
                    pawn->OnMoveRight();
                    pawn->OnButtonRight();
                } else if (event.cbutton.button == SDL_CONTROLLER_BUTTON_A) {
                    pawn->OnButtonA();
                } else if (event.cbutton.button == SDL_CONTROLLER_BUTTON_B) {
                    pawn->OnButtonB();
                } else if (event.cbutton.button == SDL_CONTROLLER_BUTTON_X) {
                    pawn->OnButtonX();
                } else if (event.cbutton.button == SDL_CONTROLLER_BUTTON_Y) {
                    pawn->OnButtonY();
                }
                break;
            case SDL_CONTROLLERBUTTONUP:
                if (event.cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_UP) {
                    pawn->OnStopMoveUp();
                } else if (event.cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_DOWN) {
                    pawn->OnStopMoveDown();
                } else if (event.cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_LEFT) {
                    pawn->OnStopMoveLeft();
                } else if (event.cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_RIGHT) {
                    pawn->OnStopMoveRight();
                }
                break;
            case SDL_FINGERDOWN:
                osc->OnButtonPress((event.tfinger.x * screen_width), (event.tfinger.y * screen_height));
                break;
            case SDL_FINGERUP:
                osc->OnButtonDepress((event.tfinger.x * screen_width), (event.tfinger.y * screen_height));
                break;
            default:
                break;
        }
    }
}

void Controller::OSC_SendInput() {
    int pB = osc->GetPressedButtons();
    if ((pB & 1) != 0) {
        pawn->OnButtonUp();
        pawn->OnMoveUp();
    } else if ((pB & 2) != 0) {
        pawn->OnButtonDown();
        pawn->OnMoveDown();
    } else {
        pawn->OnStopMoveUp();
    }

    if ((pB & 4) != 0) {
        pawn->OnMoveLeft();
        pawn->OnButtonLeft();
    } else if ((pB & 8) != 0) {
        pawn->OnMoveRight();
        pawn->OnButtonRight();
    } else {
        pawn->OnStopMoveLeft();
    }

    if ((pB & 16) != 0) pawn->OnButtonA();
    if ((pB & 32) != 0) pawn->OnButtonB();
    if ((pB & 64) != 0) pawn->OnButtonX();
    if ((pB & 128) != 0) pawn->OnButtonY();

    if ((pB & 256) != 0) pawn->OnButtonStart();
}
#else
void Controller::Mobile_ProcessInput() {
    //no ops
}

void Controller::OSC_SendInput() {
    //no ops
}
#endif