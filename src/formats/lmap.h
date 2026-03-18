#pragma once

#include <stdint.h>
#include <common/types.h>
#include <common/vector.h>

struct EntityDef {
    char name[64];
    EntityType type;
    uint16_t x;
    uint16_t y;
    uint16_t width;
    uint16_t height;
    Orientation orientation;
    char file[128];
};

struct SpawnDef {
    char name[64];
    Vector2 location;
};

struct LMAPHeader 
{
    char magic[4];
    uint16_t version;
    uint16_t width;
    uint16_t height;
    char tileset[64];
    uint16_t tiles[64 * 64];
    CollisionType colTile[256];
    EntityDef entities[64];
    SpawnDef spawnpoints[16];
    char music[64];
    char skybox[64];
};

class LMAPLoader
{
    public:
    LMAPLoader() : file("") {}
    LMAPLoader(const char* file);
    LMAPHeader load();

    private:
    const char* file;
};