#pragma once
#include <stdint.h>

enum CollisionType : uint8_t
{
    NONE,
    NORTH,
    SOUTH,
    EAST,
    WEST,
    NEO,
    SEO,
    NWO,
    SWO,
    NEI,
    SEI,
    NWI,
    SWI
};

enum GameState : uint8_t
{
    WORLD,
    BATTLE,
    MENU,
    EXIT,
    TRANSITION
};

enum EntityType : uint8_t
{
    TRIGGER_LUA,
    TRIGGER_WARP,
    TRIGGER_BATTLEFIELD,
    INTERACT_NPC,
    INTERACT_LUA,
    OBSTACLE
};

struct Entity {
    const char* name;
    EntityType type;
    int x;
    int y;
    int width;
    int height;
};