#pragma once
#include <SDL/SDL.h>

#include "SDL_Renderer.h"

struct SDL_Texture {
    SDL_Surface* surface = nullptr;
    Uint16 width, height = 0;
    Uint8 r, g, b = 255;

    void Destroy() { SDL_FreeSurface(surface); }

    ~SDL_Texture() {
        if (surface) SDL_FreeSurface(surface);
    }
};

static void SDL_DestroyTexture(SDL_Texture * texture) {
    delete texture;
}

static int SDL_QueryTexture(SDL_Texture * texture, Uint32* format, int* access, Uint16* w, Uint16* h) {
    if (!texture) return -1;

    if (format) *format = texture->surface->format->colorkey;
    if (access) *access = 0;
    if (w) *w = texture->surface->w;
    if (h) *h = texture->surface->h;

    return 0;
}

static void SDL_SetTextureColorMod(SDL_Texture * texture, Uint8 r, Uint8 g, Uint8 b) {
    //TO:DO use SDL_gfx
}