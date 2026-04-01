#include <platform/platform.h>
#include <platform/universalsdl.h>

#include "controller.h"

#ifdef LIB_SDL2
void Controller::PSP_ProcessInput() {
    if (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                pawn->OnQuit();
                break;
            case SDL_CONTROLLERDEVICEADDED:
                // Connect a controller when it is connected
                SDL_GameControllerOpen(event.cdevice.which);
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
            default:
                break;
        }
    }
}
#endif

#ifdef LIB_SDL1
void Controller::PSP_ProcessInput() {

}
#endif
