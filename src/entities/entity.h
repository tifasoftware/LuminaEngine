#pragma once
#include "formats/lmap.h"
#include "graphics/Renderer.h"
#include "graphics/sprites/sprite.h"
#include "graphics/sprites/charactersprite.h"

static const int MAX_ENTITIES = 64;
static const int MAX_PROPERTIES = 16;

class Entity {
public:
    Entity() : x(0), y(0), w(0), h(0), trigger_x(0), trigger_y(0), trigger_h(0), trigger_w(0), moveX(0), moveY(0), sprite(nullptr), type(EntityType::NO_ENTITY), centerSprite(false), orientation(FACE_NONE) {};
    virtual ~Entity() { disposeSprite(); }
    int getX() { return x; }
    int getY() { return y; }

    virtual EntityType getType() { return type; }

    void initializeSprite(int ti);
    void disposeSprite();

    void calculateTriggerBounds();

    const char* getProperty(const char* key);
    int getPropertyIndex(const char* key);
    bool hasProperty(const char* key);

    bool isInTrigger(int charX, int charY);

    bool canBeDrawn(int screenOffsetX, int screenOffsetY);
    void draw(Renderer* r, int screenOffsetX, int screenOffsetY);

    void update();
    void interact();

    //Test Methods
    void npcMoveTest();
    void npcTalkTest();

    static Entity* spawnEntity(EntityDef def);
protected:
    int x;
    int y;
    int w;
    int h;

    int trigger_x;
    int trigger_y;
    int trigger_w;
    int trigger_h;

    int moveX;
    int moveY;

    int frames = 0;
    int seconds = 0;

    bool centerSprite;

    EntityType type;
    Orientation orientation;
    EntityProperty properties[MAX_PROPERTIES];
    Sprite* sprite;
    int spriteOffsetX = 0;
    int spriteOffsetY = 0;

    int getLeftX() {
        if (centerSprite) return x - (w / 2);
        return x;
    }
    int getTopY() {
        if (centerSprite) return y - (h / 2);
        return y;
    }
    int getRightX() { return x + (w / 2); }
    int getBottomY() { return y + (h / 2); }
};
