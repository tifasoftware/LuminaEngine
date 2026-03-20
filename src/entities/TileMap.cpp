#include <SDL.h>
#include <SDL_image.h>
#include <pspkernel.h>
#include <pspdisplay.h>
#include <entities/TileMap.h>
#include <formats/lmap.h>
#include "entity.h"
#include "graphics/TextureOptimization.h"

TileMap::TileMap(const char* f, Renderer* r)
{
    renderer = r;

    file = f;
}

Entity* TileMap::getCollidingTrigger(int charX, int charY) {
    int globalX = toWorldX(charX);
    int globalY = toWorldY(charY);

    for (int i = 0; i < MAX_ENTITIES; i++) {
        Entity* e = entities[i];

        if (e != nullptr && e->isInTrigger(globalX, globalY)) return e;
    }
    return nullptr;
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
    if (skyIndex != -1) {
        for (int x = 0; x < (SCREEN_W / skyTileSize) + 1; x++) {
            for (int y = 0; y < (SCREEN_H / skyTileSize) + 1; y++) {
                renderer->drawTile(skyIndex, x * skyTileSize, y * skyTileSize);
            }
        }
    }

    int startTileX = (offsetX / TILE_SIZE) - 1;
    int startTileY = (offsetY / TILE_SIZE) - 1;

    if (startTileX < 0) startTileX = 0;
    if (startTileY < 0) startTileY = 0;

    int endTileX = TILE_W + startTileX;
    int endTileY = TILE_H + startTileY;

    for (int x = startTileX; x < endTileX; x++){
        for (int y = startTileY; y < endTileY; y++){
            if (tiles[x][y] > 0) renderer->drawTile(textureAddress, tiles[x][y], (x * TILE_SIZE) - offsetX, (y * TILE_SIZE) - offsetY);
        }
    }

    for (int i = 0; i < 64; i++) {
        if (entities[i] != nullptr) {
            Entity* e = entities[i];
            e->draw(renderer, offsetX, offsetY);
            //renderer->drawTile(0,0,toScreenX(e->getX()), toScreenY(e->getY())); //Remove when working
        }
    }
}

void TileMap::disposeMap() {
    for (int i = 0; i < MAX_ENTITIES; i++) {
        if (entities[i] != nullptr) {
            delete entities[i];
            entities[i] = nullptr;
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

    TextureOptimization to = TextureOptimization();

    for (int i = 0; i < 64; i++) {
        EntityDef def = lmap.entities[i];

        Entity* e = Entity::spawnEntity(def);

        if (e != nullptr) {

            if (e->hasProperty("texture")) {
                auto filename = e->getProperty("texture");
                int index = to.getIndex(filename);

                if (index == -1) {
                    int newIndex = renderer->loadTexture(filename);
                    to.registerFileName(filename, newIndex);
                    index = newIndex;
                }

                e->initializeSprite(index);
            };
        }

        entities[i] = e;
    }

    memcpy(spawns, lmap.spawnpoints, sizeof(spawns));
    strncpy(bgm, lmap.music, 63);
    strncpy(sky, lmap.skybox, 63);

    if (strcmp(sky, "") != 0) {
        skyIndex = renderer->loadTexture(sky);

        auto skyTex = renderer->getTexture(skyIndex);
        skyTileSize = skyTex->get_tile_size();
    } else {
        skyIndex = -1;
    }

    return true;
}

//This algorithm is rudimentary, as its set to the bounds of the psp's screen for now.
bool TileMap::isColliding(int x, int y)
{
    int playerTileX = (toWorldX(x) / TILE_SIZE);
    int playerTileY = (toWorldY(y) / TILE_SIZE);

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

bool TileMap::scrollX(int x, int cX)
{
    if (cX > SCROLL_L && cX < SCROLL_R)
    {
        return false;
    } 
    else 
    {
        offsetX += x;
        //if (offsetX + x <= 0) offsetX = 0;
        return true;
    }

}

bool TileMap::scrollY(int y, int cY)
{
    if (cY > SCROLL_T && cY < SCROLL_D)
    {
        return false;
    } 
    else 
    {
        offsetY += y;
        //if (offsetY + y <= 0) offsetY = 0;
        return true;
    }

}

int TileMap::findSpawn(const char *spawnname) {
    for (int i = 0; i < MAX_SPAWNS; i++) {
        if (strcmp(spawns[i].name, spawnname) == 0) selectedSpawn = i;
    }
    return selectedSpawn;
}

void TileMap::preShift(int x, int y)
{
    offsetX = x;
    offsetY = y;
}
