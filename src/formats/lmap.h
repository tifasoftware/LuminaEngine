#pragma once

#include <stdint.h>
#include <common/types.h>

struct Entity {
    char name[64];
    EntityType type;
    uint16_t x;
    uint16_t y;
    uint16_t width;
    uint16_t height;
    Orientation orientation;
    char file[128];
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
    Entity entities[64];
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