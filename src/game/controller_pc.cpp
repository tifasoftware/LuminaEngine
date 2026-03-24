#include <SDL2/SDL_events.h>

#include "controller.h"

void Controller::PC_ProcessInput() {
    if (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                pawn->OnQuit();
                break;
            case SDL_CONTROLLERDEVICEADDED:
                // Connect a controller when it is connected
                SDL_GameControllerOpen(event.cdevice.which);
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
                }
                break;
            default:
                break;
        }
    }
    const Uint8* keys = SDL_GetKeyboardState(NULL);
    if (keys[SDL_SCANCODE_UP] || keys[SDL_SCANCODE_W]) {
        pawn->OnMoveUp();
    } else if (keys[SDL_SCANCODE_DOWN] || keys[SDL_SCANCODE_S]) {
        pawn->OnMoveDown();
    } else {
        pawn->OnStopMoveDown();
    }
    if (keys[SDL_SCANCODE_LEFT] || keys[SDL_SCANCODE_A]) {
        pawn->OnMoveLeft();
    } else if (keys[SDL_SCANCODE_RIGHT] || keys[SDL_SCANCODE_D]) {
        pawn->OnMoveRight();
    } else {
        pawn->OnStopMoveRight();
    }

}
