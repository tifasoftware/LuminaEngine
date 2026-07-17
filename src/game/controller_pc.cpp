#include <ios>
#include <platform/platform.h>
#include <platform/universalsdl.h>

#include "controller.h"

//#ifdef LIB_SDL2
void Controller::PC_ProcessInput() {
    if (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                pawn->OnQuit();
                break;
            case SDL_CONTROLLERDEVICEADDED:
                // Connect a controller when it is connected
#ifdef LIB_SDL1
                //no ops
#else
                SDL_GameControllerOpen(event.cdevice.which);
#endif
                break;
            case SDL_KEYDOWN:
                if(event.key.keysym.sym == SDLK_ESCAPE) {
                    pawn->OnButtonStart();
                } else if (event.key.keysym.sym == SDLK_SPACE) {
                    pawn->OnButtonSelect();
                } else if (event.key.keysym.sym == SDLK_RETURN) {
                    pawn->OnButtonA();
                } else if (event.key.keysym.sym == SDLK_BACKSPACE) {
                    pawn->OnButtonB();
                } else if (event.key.keysym.sym == SDLK_e) {
                    pawn->OnButtonX();
                } else if (event.key.keysym.sym == SDLK_TAB) {
                    pawn->OnButtonY();
                } else if (event.key.keysym.sym == SDLK_UP) {
                    pawn->OnButtonUp();
                } else if (event.key.keysym.sym == SDLK_DOWN) {
                    pawn->OnButtonDown();
                } else if (event.key.keysym.sym == SDLK_LEFT) {
                    pawn->OnButtonLeft();
                } else if (event.key.keysym.sym == SDLK_RIGHT) {
                    pawn->OnButtonRight();
                }
                break;
#ifdef LIB_SDL2
            case SDL_CONTROLLERBUTTONDOWN:
                if(event.cbutton.button == SDL_CONTROLLER_BUTTON_START) {
                    pawn->OnButtonStart();
                } else if (event.cbutton.button == SDL_CONTROLLER_BUTTON_BACK) {
                    pawn->OnButtonSelect();
                } else if (event.cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_UP) {
                    pawn->OnMoveUp();
                    pawn->OnButtonUp();
                    upDownController = true;
                } else if (event.cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_DOWN) {
                    pawn->OnMoveDown();
                    pawn->OnButtonDown();
                    upDownController = true;
                } else if (event.cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_LEFT) {
                    pawn->OnMoveLeft();
                    pawn->OnButtonLeft();
                    leftRightController = true;
                } else if (event.cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_RIGHT) {
                    pawn->OnMoveRight();
                    pawn->OnButtonRight();
                    leftRightController = true;
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
                    upDownController = false;
                } else if (event.cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_DOWN) {
                    pawn->OnStopMoveDown();
                    upDownController = false;
                } else if (event.cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_LEFT) {
                    pawn->OnStopMoveLeft();
                    leftRightController = false;
                } else if (event.cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_RIGHT) {
                    pawn->OnStopMoveRight();
                    leftRightController = false;
                }
                break;
#endif
            default:
                break;
        }
    }
    const Uint8* keys = SDL_GetKeyboardState(NULL);
    if (keys[SDL_SCANCODE_UP] || keys[SDL_SCANCODE_W]) {
        pawn->OnMoveUp();
    } else if (keys[SDL_SCANCODE_DOWN] || keys[SDL_SCANCODE_S]) {
        pawn->OnMoveDown();
    } else if (!upDownController) {
        pawn->OnStopMoveDown();
    }
    if (keys[SDL_SCANCODE_LEFT] || keys[SDL_SCANCODE_A]) {
        pawn->OnMoveLeft();
    } else if (keys[SDL_SCANCODE_RIGHT] || keys[SDL_SCANCODE_D]) {
        pawn->OnMoveRight();
    } else if (!leftRightController) {
        pawn->OnStopMoveRight();
    }

}
//#endif
//#ifdef LIB_SDL1
//void Controller::PC_ProcessInput() {
//
//}
//#endif
