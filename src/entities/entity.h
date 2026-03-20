#pragma once
#include "formats/lmap.h"
#include "graphics/Renderer.h"
#include "graphics/sprites/sprite.h"
#include "graphics/sprites/charactersprite.h"

static const int MAX_ENTITIES = 64;
static const int MAX_PROPERTIES = 16;

class Entity {
public:
    Entity() : x(0), y(0), w(0), h(0), sprite(nullptr), type(EntityType::NO_ENTITY), centerSprite(false) {};
    virtual ~Entity() { disposeSprite(); }
    int getX() { return x; }
    int getY() { return y; }

    virtual EntityType getType() { return type; }

    void initializeSprite(int ti);
    void disposeSprite();

    const char* getProperty(const char* key);
    int getPropertyIndex(const char* key);
    bool hasProperty(const char* key);

    bool isInTrigger(int charX, int charY);

    bool canBeDrawn(int screenOffsetX, int screenOffsetY);
    void draw(Renderer* r, int screenOffsetX, int screenOffsetY);

    void update();

    static Entity* spawnEntity(EntityDef def);
protected:
    int x;
    int y;
    int w;
    int h;

    int moveX;
    int moveY;

    bool centerSprite;

    EntityType type;
    EntityProperty properties[MAX_PROPERTIES];
    Sprite* sprite;

    int getLeftX() { return x - (w / 2); }
    int getTopY() { return y - (h / 2); }
    int getRightX() { return x + (w / 2); }
    int getBottomY() { return y + (h / 2); }
};
