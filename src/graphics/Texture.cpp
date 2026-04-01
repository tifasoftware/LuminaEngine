#include <platform/platform.h>
#include <platform/universalsdl.h>
#include <graphics/Texture.h>

#include "common/utils.h"

Texture::Texture(const char* file, SDL_Renderer* render){
    printf("New Texture");
    //SDL_Surface * pixels = IMG_Load(LuminaUtils::osPath(file).c_str());
    SDL_Surface* pixels = nullptr;
    if (!pixels) {
        pixels = SDL_CreateRGBSurface(
        SDL_SWSURFACE, 16, 16, render->screen->format->BitsPerPixel,
            render->screen->format->Rmask,
            render->screen->format->Gmask,
            render->screen->format->Bmask,
            render->screen->format->Amask
        );
        Uint32 black = SDL_MapRGB(render->screen->format, 0, 0, 0);
        Uint32 purple = SDL_MapRGB(render->screen->format, 128, 0, 128);

        SDL_LockSurface(pixels);

        for (int y = 0; y < 16; ++y) {
            for (int x = 0; x < 16; ++x) {
                Uint32 color = ((x/4 + y/4) % 2 == 0) ? black : purple;
                if (render->screen->format->BytesPerPixel == 2) {
                    ((Uint16*)pixels->pixels)[y * 16 + x] = color;
                } else {
                    Uint32* rpixels = (Uint32*)pixels->pixels;
                    rpixels[y * 16 + x] = color;
                }
            }
        }

        SDL_UnlockSurface(pixels);
    }
    tex = SDL_CreateTextureFromSurface(render, pixels);
    SDL_FreeSurface(pixels);

    SDL_Rect sprite_rect;
    SDL_QueryTexture(tex, NULL, NULL, &sprite_rect.w, &sprite_rect.h);

    width = sprite_rect.w;
    height = sprite_rect.h;

    if (width >= height){
        tile_size = width;
    } else {
        tile_size = height;
    }

    isOpen = false;
}

int Texture::release(){
    if (tex != nullptr) {
        SDL_DestroyTexture(tex);
        tex = nullptr;
        isOpen = true;
        return 0;
    }
    return -1;
}