#pragma once
#include "formats/lmap.h"

class Entity {
public:
    Entity() : x(0), y(0), w(0), h(0) {};
    ~Entity() {}

    static Entity* spawnEntity(EntityDef def);
protected:
    int x;
    int y;
    int w;
    int h;
};
