#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <graphics/Texture.h>

static const int MAX_TEXTURES = 64;

class Renderer
{
public:
    Renderer(SDL_Window * win);
    int drawTile(int texIndex, int x, int y);
    int drawSprite(int texIndex, int x, int y);
    int loadTexture(const char* file);
    int unloadAllTextures();
    void clear();
    void present();
    void shutdown();

private:
    SDL_Renderer* sdl_r;
    Texture m_textures[MAX_TEXTURES];
    int m_texture_count = 0;
};