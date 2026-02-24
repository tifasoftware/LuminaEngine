#include <SDL.h>
#include <SDL_image.h>
#include <graphics/Renderer.h>
#include <algorithm>

Renderer::Renderer(SDL_Window * win) {
    sdl_r = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
}

int Renderer::loadTexture(const char* file) {
    if (m_texture_count >= MAX_TEXTURES) {
        return -1;
    }
    m_textures[m_texture_count] = Texture(file, sdl_r);
    return m_texture_count++;
}

int Renderer::unloadAllTextures(){
    for (int i = 0; i < MAX_TEXTURES; i++){
        m_textures[i].release();
    }
    m_texture_count = 0;
    return 0;
}

int Renderer::drawTile(int texIndex, int x, int y){

    Texture* tex = &m_textures[texIndex];

    SDL_Rect sprite_rect;
    sprite_rect.w = tex->get_tile_size();
    sprite_rect.h = sprite_rect.w;
    sprite_rect.x = x;
    sprite_rect.y = y;

    SDL_RenderCopy(sdl_r, tex->get_SDLTex() , NULL, &sprite_rect);

    return 0;
}

int Renderer::drawSprite(int texIndex, int x, int y){

    Texture* tex = &m_textures[texIndex];

    SDL_Rect sprite_rect;
    sprite_rect.w = tex->get_sprite_width();
    sprite_rect.h = tex->get_sprite_height();
    sprite_rect.x = x;
    sprite_rect.y = y;

    SDL_RenderCopy(sdl_r, tex->get_SDLTex() , NULL, &sprite_rect);

    return 0;
}

void Renderer::floodOverlay(int r, int g, int b, int alpha)
{
    alpha = std::max(0, std::min(255, alpha));
    SDL_SetRenderDrawBlendMode(sdl_r, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(sdl_r, r, g, b, alpha);

    SDL_Rect screen = { 0, 0, 480, 272 };
    SDL_RenderFillRect(sdl_r, &screen);

    SDL_SetRenderDrawBlendMode(sdl_r, SDL_BLENDMODE_NONE);
}

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
    SDL_DestroyRenderer(sdl_r);
}

Texture* Renderer::getTexture(int index)
{
    return &m_textures[index];
}