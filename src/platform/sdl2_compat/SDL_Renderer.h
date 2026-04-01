#pragma once
#include <SDL/SDL.h>
#include "SDL_Texture.h"
#include "SDL_Window.h"

struct SDL_Renderer {
    SDL_Surface* screen;
    bool SDL_BP_AlphaMode = false;
    Uint32 clear_color;
    Uint32 drawcolor;
    int alpha = 255;

    void RenderClear() {
        SDL_FillRect(screen, NULL, clear_color);
    }

    void RenderCopy(SDL_Texture* texture, SDL_Rect* src, SDL_Rect* dst) {
        bool needToDelete = false;
        if (!src) {
            src = new SDL_Rect();
            src->x = 0;
            src->y = 0;
            src->w = texture->width;
            src->h = texture->height;
            needToDelete = true;
        }
        SDL_BlitSurface(texture->surface, src, screen, dst);
        if (needToDelete) delete src;
    }

    void RenderPresent() {
        SDL_Flip(screen);
    }

    void FillRect(SDL_Rect* rect) {
        SDL_FillRect(screen, rect, drawcolor);
    }

    void DrawRect(SDL_Rect* rect) {
        SDL_Rect lineRect = {rect->x, rect->y, rect->w, 1};
        FillRect(&lineRect);

        lineRect.y = rect->y + rect->h - 1;
        FillRect(&lineRect);

        lineRect.x = rect->x;
        lineRect.y = rect->y;
        lineRect.w = 1;
        lineRect.h = rect->h;
        FillRect(&lineRect);

        lineRect.x = rect->x + rect->w - 1;
        FillRect(&lineRect);
    }
};

static void SDL_RenderClear(SDL_Renderer * renderer) {
    renderer->RenderClear();
}

static void SDL_RenderPresent(SDL_Renderer * renderer) {
    renderer->RenderPresent();
}

static void SDL_RenderCopy(SDL_Renderer* renderer, SDL_Texture* texture, SDL_Rect* src, SDL_Rect* dst) {
    renderer->RenderCopy(texture, src, dst);
}

enum SDL_BlendMode {
    SDL_BLENDMODE_NONE = 0,
    SDL_BLENDMODE_BLEND,
    SDL_BLENDMODE_ADD,
    SDL_BLENDMODE_MOD,
};

static void SDL_SetRenderDrawBlendMode(SDL_Renderer * renderer, SDL_BlendMode mode) {
    if (mode == SDL_BLENDMODE_BLEND) {
        renderer->SDL_BP_AlphaMode = true;
    } else {
        renderer->SDL_BP_AlphaMode = false;
    }
}

static void SDL_SetRenderDrawColor(SDL_Renderer * renderer, int r, int g, int b, int a) {
    renderer->drawcolor = SDL_MapRGB(renderer->screen->format, r, g, b);
    if (renderer->SDL_BP_AlphaMode) {
        renderer->alpha = a;
    }
}

static void SDL_RenderFillRect(SDL_Renderer * renderer, SDL_Rect* rect) {
    renderer->FillRect(rect);
}

static void SDL_RenderDrawRect(SDL_Renderer * renderer, SDL_Rect* rect) {
    renderer->DrawRect(rect);
}

static SDL_Texture* SDL_CreateTextureFromSurface(SDL_Renderer * renderer, SDL_Surface* surface) {
    SDL_Texture* texture = new SDL_Texture();
    texture->surface = SDL_DisplayFormat(surface);
    texture->height = texture->surface->h;
    texture->width = texture->surface->w;
    return texture;
}

static SDL_Renderer* SDL_CreateRenderer(SDL_Window * window, int index, int flags) {
    auto* r = new SDL_Renderer();
    r->screen = window;
    r->clear_color = SDL_MapRGB(window->format, 255, 0, 0);
    r->RenderClear();
    return r;
}
//No Ops
static void SDL_DestroyRenderer(SDL_Renderer * renderer) {}
static void SDL_RenderSetLogicalSize(SDL_Renderer * renderer, int w, int h) {}
static void SDL_SetHint(int hint, char* value) {}
static const int SDL_RENDERER_ACCELERATED = -1;
static const int SDL_HINT_RENDER_SCALE_QUALITY = 0;
