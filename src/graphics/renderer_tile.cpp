#include <graphics/renderer.h>
#include <graphics/texture.h>

int Renderer::drawTile(int texIndex, int tileIndex, int x, int y) {
    return drawTile(texIndex, tileIndex, x, y, 16);
}

int Renderer::drawTile(int texIndex, int tileIndex, int x, int y, int tileSize){

    Texture* tex = &m_textures[texIndex];

    SDL_Rect sprite_rect;
    sprite_rect.w = tileSize;
    sprite_rect.h = tileSize;
    sprite_rect.x = x;
    sprite_rect.y = y;

    SDL_Rect src_rect;
    src_rect.w = tileSize;
    src_rect.h = tileSize;
    src_rect.x = (tileIndex % tileSize) * tileSize;
    src_rect.y = (tileIndex / tileSize) * tileSize;

    SDL_RenderCopy(sdl_r, tex->get_SDLTex() , &src_rect, &sprite_rect);

    return 0;
}

int Renderer::drawTile(int texIndex, int x, int y) {
    Texture* tex = &m_textures[texIndex];

    SDL_Rect sprite_rect;
    sprite_rect.w = tex->get_tile_size();
    sprite_rect.h = tex->get_tile_size();
    sprite_rect.x = x;
    sprite_rect.y = y;

    SDL_RenderCopy(sdl_r, tex->get_SDLTex() , NULL, &sprite_rect);
    return 0;
}

int Renderer::fillTile(int texIndex) {
    if (m_textures[texIndex].isTextureFree()) return -1;

    int skyTileSize = m_textures[texIndex].get_sprite_height();

    for (int x = 0; x < (GetWidth() / skyTileSize) + 1; x++) {
        for (int y = 0; y < (GetHeight() / skyTileSize) + 1; y++) {
            drawTile(texIndex, x * skyTileSize, y * skyTileSize);
        }
    }

    return 0;
}
