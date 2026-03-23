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
                } else if (event.key.keysym.sym == SDLK_w) {
                    pawn->OnMoveUp();
                } else if (event.key.keysym.sym == SDLK_s) {
                    pawn->OnMoveDown();
                } else if (event.key.keysym.sym == SDLK_a) {
                    pawn->OnMoveLeft();
                } else if (event.key.keysym.sym == SDLK_d) {
                    pawn->OnMoveRight();
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
            case SDL_KEYUP:
                if (event.key.keysym.sym == SDLK_w) {
                    pawn->OnStopMoveUp();
                } else if (event.key.keysym.sym == SDLK_s) {
                    pawn->OnStopMoveDown();
                } else if (event.key.keysym.sym == SDLK_a) {
                    pawn->OnStopMoveLeft();
                } else if (event.key.keysym.sym == SDLK_d) {
                    pawn->OnStopMoveRight();
                }
                break;
            default:
                break;
        }
    }
}
