#include <SDL.h>
#include <SDL_image.h>
#include <graphics/Texture.h>

Texture::Texture(const char* file, SDL_Renderer* render){
    SDL_Surface * pixels = IMG_Load(file);
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
}

int Texture::release(){
    if (tex != nullptr) {
        SDL_DestroyTexture(tex);
        tex = nullptr;
        return 0;
    }
    return -1;
}