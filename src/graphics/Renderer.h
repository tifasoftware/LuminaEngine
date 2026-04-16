#pragma once

#include <platform/platform.h>
#include <platform/universalsdl.h>
#include <graphics/Texture.h>

static const int MAX_TEXTURES = 64;
#ifdef PLATFORM_3DS
static const int FRAME_RATE = 60;
#else
static const int FRAME_RATE = 60;
#endif
static const int REDRAW_DELAY = 1000 / FRAME_RATE;

class Renderer
{
public:
    Renderer(SDL_Window* win);
    int drawTile(int texIndex, int tileIndex, int x, int y);
    int drawTile(int texIndex, int tileIndex, int x, int y, int tileSize);
    int drawTile(int texIndex, int x, int y);
    int drawSprite(int texIndex, int x, int y);
    int drawSubSprite(int texIndex, int x, int y, int cX, int cY, int cW, int cH);
    int loadTexture(const char* file);
    int unloadAllTextures();
    int unloadTexture(int index);
    void floodOverlay(int r, int g, int b, int alpha);
#ifdef LIB_SDL1
    void floodOldOverlay();
#else
    void floodOldOverlay() {}
#endif
    void clear();
    void present();
    void shutdown();
    Texture* getTexture(int index);
    SDL_Renderer* getRenderer() const { return sdl_r; }

private:
    SDL_Renderer* sdl_r;

    #ifdef LIB_SDL1
    SDL_Surface* fade_surface;
    #endif

    Texture m_textures[MAX_TEXTURES];
    int m_texture_count = 0;
    int firstOpenSlot();
};