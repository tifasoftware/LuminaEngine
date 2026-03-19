#pragma once
#include "formats/lmap.h"

static const int MAX_ENTITIES = 64;
static const int MAX_PROPERTIES = 16;

class Entity {
public:
    Entity() : x(0), y(0), w(0), h(0) {};
    virtual ~Entity() {}
    int getX() { return x; }
    int getY() { return y; }

    virtual EntityType getType() { return NO_ENTITY; }

    const char* getProperty(const char* key);
    bool hasProperty(const char* key);

    static Entity* spawnEntity(EntityDef def);
protected:
    int x;
    int y;
    int w;
    int h;

    EntityType type;
    EntityProperty properties[MAX_PROPERTIES];
};
