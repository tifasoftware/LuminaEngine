#pragma once

#include <SDL.h>
#include <SDL_image.h>

class Texture
{
public:
    Texture() : tex(nullptr), tile_size(16), width(16), height(16) {}
    Texture(const char* file, SDL_Renderer* render);
    int release();
    SDL_Texture* get_SDLTex() const { return tex; }
    int get_tile_size() const { return tile_size; }
    int get_sprite_height() const { return height; }
    int get_sprite_width () const { return width; }

private:
    SDL_Texture* tex;
    int tile_size;
    int width;
    int height;
};