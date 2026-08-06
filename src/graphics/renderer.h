#pragma once

#include <platform/platform.h>
#include <platform/universalsdl.h>
#include <graphics/texture.h>

#include "formats/ltl/ltl.h"

//MAX_TEXTURES
// 8 SYSTEM + 64 USER = 72 TOTAL
static const int MAX_TEXTURES = 72;
static const int MAX_FONTS = 4;
#ifdef PLATFORM_3DS
static const int FRAME_RATE = 60;
#else
static const int FRAME_RATE = 60;
#endif
static const int REDRAW_DELAY = 1000 / FRAME_RATE;

//SYSTEM TEXTURES
static const int MAX_SYS_TEXTURES = 8;
#define SYSTEX_FONT_REG 0
#define SYSTEX_FONT_BOLD 1
#define SYSTEX_FONT_ITAL 2
#define SYSTEX_FONT_BDIT 3
#define SYSTEX_OSC_BTNS 4
#define SYSTEX_OSC_MENU 5

class Renderer
{
public:
    Renderer(SDL_Window* win);
    int drawTile(int texIndex, int tileIndex, int x, int y);
    int drawTile(int texIndex, int tileIndex, int x, int y, int tileSize);
    int drawTile(int texIndex, int x, int y);
    int drawSprite(int texIndex, int x, int y);
    int drawSubSprite(int texIndex, int x, int y, int cX, int cY, int cW, int cH);

    int drawPlainText(const char* text, int x, int y, int font, int r, int g, int b);
    int drawLTLText(CompiledLTL* ltl, int font, int x, int y) ;

    int loadTexture(const char* file);
    void loadTexture(const char* file, int index);
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

    int GetWidth() { return width; }
    int GetHeight() { return height; }

private:
    SDL_Renderer* sdl_r;

    #ifdef LIB_SDL1
    SDL_Surface* fade_surface;
    #endif

    Texture m_textures[MAX_TEXTURES];
    Texture m_fonts[MAX_FONTS];
    int m_texture_count = 0;
    int firstOpenSlot();

    int width;
    int height;
};