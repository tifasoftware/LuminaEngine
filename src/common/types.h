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

enum GameState
{
    WORLD,
    BATTLE,
    MENU,
    EXIT,
    TRANSITION
};