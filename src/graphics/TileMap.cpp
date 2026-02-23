#include <SDL.h>
#include <SDL_image.h>
#include <pspkernel.h>
#include <pspdisplay.h>
#include <graphics/TileMap.h>

TileMap::TileMap(Renderer* r)
{
    renderer = r;
    r->loadTexture("grass.png");
}

void TileMap::drawMap()
{
    for (int x = 0; x < tileW; x++){
        for (int y = 0; y < tileH; y++){
            renderer->drawTile(0, x * tileSize, y * tileSize);
        }
    }
}