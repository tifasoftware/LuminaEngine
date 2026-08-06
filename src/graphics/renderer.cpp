#include <platform/platform.h>
#include <platform/universalsdl.h>
#include <graphics/renderer.h>
#include <graphics/texture.h>
#include <algorithm>

#ifdef PLATFORM_ANDROID
#include <platform/mobile/mdisplay.h>
#endif

Renderer::Renderer(SDL_Window * win) {
#ifdef PLATFORM_DREAMCAST
    //sdl_r = SDL_CreateRenderer(win, -1, 0);
    sdl_r = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
#else
    sdl_r = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
#endif
#ifdef PLATFORM_PC
    SDL_RenderSetLogicalSize(sdl_r, 480, 272);
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0");
#endif
#ifdef PLATFORM_ANDROID
    SDL_RenderSetLogicalSize(sdl_r, MobileDisplay::GetDrawWidth(), MobileDisplay::GetDrawHeight());
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0");
#endif

#ifdef LIB_SDL1
    fade_surface = SDL_DisplayFormatAlpha(win);
    SDL_SetAlpha(fade_surface, SDL_SRCALPHA, SDL_ALPHA_OPAQUE);
#endif

#ifdef PLATFORM_ANDROID
    height = MobileDisplay::GetDrawHeight();
    width = MobileDisplay::GetDrawWidth();
#else
    height = SCREEN_H;
    width = SCREEN_W;
#endif

// Load System Textures
    loadTexture("fontatlas.png", SYSTEX_FONT_REG);
    //loadTexture("", SYSTEX_FONT_BOLD);
    //loadTexture("", SYSTEX_FONT_ITAL);
    //loadTexture("", SYSTEX_FONT_BDIT);

#if (defined(PLATFORM_PC) && defined(USER_LIGHTNING)) || defined(PLATFORM_ANDROID)
    loadTexture("mobilecontrols_15.png", SYSTEX_OSC_BTNS);
    loadTexture("mobilecontrols2.png", SYSTEX_OSC_MENU);
#endif
}

int Renderer::firstOpenSlot()
{
    for (int i = MAX_SYS_TEXTURES; i < MAX_TEXTURES; i++)
    {
        if (m_textures[i].isTextureFree())
        {
            return i;
        }
    }
    return -1;
}

int Renderer::loadTexture(const char* file) 
{
    int slot = firstOpenSlot();

    if (slot != -1)
    {
        loadTexture(file, slot);
    }
    
    return slot;
}

void Renderer::loadTexture(const char* file, int index) {
    m_textures[index] = Texture(file, sdl_r);
}

int Renderer::unloadAllTextures(){
    for (int i = MAX_SYS_TEXTURES; i < MAX_TEXTURES; i++){
        m_textures[i].release();
    }
    m_texture_count = 0;
    return 0;
}

int Renderer::unloadTexture(int index) {
    m_textures[index].release();
    m_texture_count--;
    return 0;
}


void Renderer::floodOverlay(int r, int g, int b, int alpha)
{
    alpha = std::max(0, std::min(255, alpha));
    SDL_Rect screen = { 0, 0, GetWidth(), GetHeight() };

#ifdef LIB_SDL1
    SDL_FillRect(fade_surface, &screen, SDL_MapRGBA(fade_surface->format, r, g, b, alpha));

    SDL_BlitSurface(fade_surface, &screen, sdl_r->screen, &screen);
#else
    SDL_SetRenderDrawBlendMode(sdl_r, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(sdl_r, r, g, b, alpha);


    SDL_RenderFillRect(sdl_r, &screen);

    SDL_SetRenderDrawBlendMode(sdl_r, SDL_BLENDMODE_NONE);
#endif
}

#ifdef LIB_SDL1
void Renderer::floodOldOverlay()
{
    SDL_Rect screen = { 0, 0, SCREEN_W, SCREEN_H };
    SDL_BlitSurface(fade_surface, &screen, sdl_r->screen, &screen);
}
#endif

void Renderer::clear()
{
    SDL_RenderClear(sdl_r);
}

void Renderer::present()
{
    SDL_SetRenderDrawBlendMode(sdl_r, SDL_BLENDMODE_NONE);
    SDL_SetRenderDrawColor(sdl_r, 0, 0, 0, 255);
    SDL_RenderPresent(sdl_r);
}

void Renderer::shutdown()
{
#ifdef LIB_SDL1
    SDL_FreeSurface(fade_surface);
#endif
    SDL_DestroyRenderer(sdl_r);
}

Texture* Renderer::getTexture(int index)
{
    return &m_textures[index];
}