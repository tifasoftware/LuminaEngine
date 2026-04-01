#pragma once

typedef SDL_Surface SDL_Window;

static SDL_Window* SDL_CreateWindow(char * name, int x, int y, int w, int h, int flags) {
    return SDL_SetVideoMode(w, h, 16, SDL_SWSURFACE);
}

//No Ops - No SDL1.2 Equivalents
static void SDL_DestroyWindow(SDL_Window * window) {}
static void SDL_RaiseWindow(SDL_Window * window) {}
static void SDL_SetWindowInputFocus(SDL_Window * window) {}
static void SDL_SetWindowFullscreen(SDL_Window * window, int fullscreen) {}


static const int SDL_WINDOWPOS_UNDEFINED = -1;