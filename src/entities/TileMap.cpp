#include <SDL.h>
#include <SDL_image.h>
#include <pspkernel.h>
#include <pspdisplay.h>
#include <entities/TileMap.h>
#include <formats/lmap.h>

TileMap::TileMap(const char* f, Renderer* r)
{
    renderer = r;

    file = f;
}

bool TileMap::loadMap()
{
    if (loadFromFile(file)) {
        return true;
    } else {
        renderer->loadTexture("grass.png");

        for (int x = 0; x < TILE_W; x++){
            for (int y = 0; y < TILE_H; y++){
                tiles[x][y] = 0;
            }
        }
    }
    return false;
}

void TileMap::drawMap()
{
    for (int x = 0; x < TILE_W; x++){
        for (int y = 0; y < TILE_H; y++){
            renderer->drawTile(textureAddress, tiles[x][y], x * TILE_SIZE, y * TILE_SIZE);
        }
    }
}

bool TileMap::loadFromFile(const char* file)
{
    LMAPLoader ll = LMAPLoader(file);

    LMAPHeader lmap = ll.load();

    if (strncmp(lmap.magic, "LMAP", 4) != 0)
    {
        SDL_Log("TileMap: failed to open %s", file);
        return false;
    }

    textureAddress = renderer->loadTexture(lmap.tileset);
    //textureAddress = renderer->loadTexture("grass.png");

    int offset = 0;
    for (int x = 0; x < 64; x++)
    {
        for (int y = 0; y < 64; y++)
        {
            int t = lmap.tiles[offset + y];
            tiles[x][y] = t;
            collision[x][y] = lmap.colTile[t];
        }
        offset += 64;
    }

    return true;
}

//This algorithm is rudimentary, as its set to the bounds of the psp's screen for now.
bool TileMap::isColliding(int x, int y)
{
    int playerTileX = (x / TILE_SIZE);
    int playerTileY = (y / TILE_SIZE);

    int collideX = playerTileX * TILE_SIZE;
    int collideY = playerTileY * TILE_SIZE;

    CollisionType ct = collision[playerTileX][playerTileY];

    switch (ct)
    {
        case NORTH:
        case SOUTH:
        case EAST:
        case WEST:
        case NEI:
        case SEI:
        case NWI:
        case SWI:
        case NEO:
        case SEO:
        case NWO:
        case SWO:
            return true;
        case NONE:
            return false;
        default:
            return false;
        break;
    }
    if (x < 16 || y < 16 || x > 464 || y > 256)
    {
        return true;
    }
    return false;
}
