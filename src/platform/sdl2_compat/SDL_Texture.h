#pragma once
#include <SDL/SDL.h>

#include "SDL_Renderer.h"

struct SDL_Texture {
    SDL_Surface* surface = nullptr;
    SDL_Surface* tinted_surface = nullptr;
    bool tinted = false;
    Uint16 width, height = 0;
    Uint8 r, g, b = 255;

    void Destroy() { SDL_FreeSurface(surface); }

    ~SDL_Texture() {
        if (tinted_surface) SDL_FreeSurface(tinted_surface);
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
    if (texture->tinted) SDL_FreeSurface(texture->tinted_surface);
    texture->tinted_surface = SDL_ConvertSurface(texture->surface, texture->surface->format, texture->surface->flags);
    Uint32 srcColor = SDL_MapRGB(texture->surface->format, 255,255,255);
    Uint32 dstColor = SDL_MapRGB(texture->surface->format, r, g, b);

    SDL_LockSurface(texture->tinted_surface);

    int pixelCount = texture->tinted_surface->h * (texture->tinted_surface->pitch / (texture->tinted_surface->format->BytesPerPixel));
    Uint32 *pixels = (Uint32 *)texture->tinted_surface->pixels;

    for (int i = 0; i < pixelCount; i++) {
        if (pixels[i] == srcColor)
            pixels[i] = dstColor;
    }

    SDL_UnlockSurface(texture->tinted_surface);
    texture->tinted = true;
}