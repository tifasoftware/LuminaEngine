#include <graphics/renderer.h>
#include <graphics/texture.h>

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

int Renderer::drawSubSprite(int texIndex, int x, int y, int cX, int cY, int cW, int cH)
{
    Texture* tex = &m_textures[texIndex];

    SDL_Rect sprite_rect;
    sprite_rect.w = cW;
    sprite_rect.h = cH;
    sprite_rect.x = x;
    sprite_rect.y = y;

    SDL_Rect src_rect;
    src_rect.w = cW;
    src_rect.h = cH;
    src_rect.x = cX;
    src_rect.y = cY;

    SDL_RenderCopy(sdl_r, tex->get_SDLTex() , &src_rect, &sprite_rect);

    return 0;
}