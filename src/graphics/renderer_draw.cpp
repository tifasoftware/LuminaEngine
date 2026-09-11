#include "renderer.h"

void Renderer::drawRect(int x, int y, int w, int h, ColorA c) {
    SDL_SetRenderDrawColor(sdl_r, c.r, c.g, c.b, c.a);
    SDL_SetRenderDrawBlendMode(sdl_r, SDL_BLENDMODE_BLEND);
    SDL_Rect box = {x, y, w, h};
    SDL_RenderDrawRect(sdl_r, &box);
}

void Renderer::fillRect(int x, int y, int w, int h, ColorA c) {
    SDL_SetRenderDrawColor(sdl_r, c.r, c.g, c.b, c.a);
    SDL_SetRenderDrawBlendMode(sdl_r, SDL_BLENDMODE_BLEND);
    SDL_Rect box = {x, y, w, h};
    SDL_RenderFillRect(sdl_r, &box);
}
