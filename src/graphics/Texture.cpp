#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <graphics/Texture.h>

#include "common/utils.h"

Texture::Texture(const char* file, SDL_Renderer* render){
    SDL_Surface * pixels = IMG_Load(LuminaUtils::osPath(file).c_str());
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