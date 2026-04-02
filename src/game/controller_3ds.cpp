#include <platform/platform.h>
#include <platform/universalsdl.h>

#include "controller.h"

void Controller::N3DS_ProcessInput() {
    if (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                pawn->OnQuit();
                break;
            case SDL_KEYDOWN:
                if(event.key.keysym.sym == SDLK_RETURN) {
                    pawn->OnButtonStart();
                } else if (event.key.keysym.sym == SDLK_ESCAPE) {
                    pawn->OnButtonSelect();
                } else if (event.key.keysym.sym == SDLK_a) {
                    pawn->OnButtonA();
                } else if (event.key.keysym.sym == SDLK_b) {
                    pawn->OnButtonB();
                } else if (event.key.keysym.sym == SDLK_x) {
                    pawn->OnButtonX();
                } else if (event.key.keysym.sym == SDLK_y) {
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
            default:
                break;
        }
    }
    const Uint8* keys = SDL_GetKeyboardState(NULL);
    if (keys[SDL_SCANCODE_UP]) {
        pawn->OnMoveUp();
    } else if (keys[SDL_SCANCODE_DOWN]) {
        pawn->OnMoveDown();
    } else {
        pawn->OnStopMoveDown();
    }
    if (keys[SDL_SCANCODE_LEFT]) {
        pawn->OnMoveLeft();
    } else if (keys[SDL_SCANCODE_RIGHT]) {
        pawn->OnMoveRight();
    } else {
        pawn->OnStopMoveRight();
    }

}