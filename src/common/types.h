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

enum MenuClass : uint8_t {
    MAIN_MENU,
    PAUSE_MENU,
    LUA_MENU,
    NO_MENU,
    NO_MENU_RETURNTOWORLD
};

enum EntityType : uint8_t
{
    TRIGGER_LUA,
    TRIGGER_WARP,
    TRIGGER_BATTLEFIELD,
    INTERACT_NPC,
    INTERACT_LUA,
    OBSTACLE,
    NO_ENTITY
};

enum Orientation : uint8_t {
    FACE_UP,
    FACE_DOWN,
    FACE_LEFT,
    FACE_RIGHT,
    //For Poly-directional entities
    FACE_LR,
    FACE_UD,
    FACE_ALL,
    FACE_NONE
};