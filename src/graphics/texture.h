#pragma once

#include <platform/platform.h>
#include <platform/universalsdl.h>

class Texture
{
public:
    Texture() : tex(nullptr), tile_size(16), width(16), height(16), isOpen(true) {}
    Texture(const char* file, SDL_Renderer* render);
    int release();
    SDL_Texture* get_SDLTex() const { return tex; }
    int get_tile_size() const { return tile_size; }
    int get_sprite_height() const { return height; }
    int get_sprite_width () const { return width; }
    bool isTextureFree() const { return isOpen; }

    void SetColor() { SetColor(255,255,255); }
    void SetColor(Uint8 r, Uint8 g, Uint8 b) { SDL_SetTextureColorMod(tex, r, g, b); }

    void SetOpacity() { SetOpacity(255); }
    void SetOpacity(Uint8 a) { SDL_SetTextureAlphaMod(tex, a); }

private:
    SDL_Texture* tex;
    bool isOpen;
    int tile_size;
    int width;
    int height;
};