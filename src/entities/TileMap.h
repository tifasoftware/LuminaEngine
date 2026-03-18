#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <cstdio>
#include <cstring>
#include <graphics/Renderer.h>
#include <formats/lmap.h>

#include "entity.h"
#include "trigger.h"

//PSP Resolution Width - 480
//PSP Resolution Height - 272
static const int SCREEN_W = 480;
static const int SCREEN_H = 272;

static const int TILE_SIZE = 16;

static const int SCROLL_T = 40;
static const int SCROLL_D = SCREEN_H - 40;
static const int SCROLL_L = 40;
static const int SCROLL_R = SCREEN_W - 40;

static const int TILE_W = (SCREEN_W / TILE_SIZE) + 2;
static const int TILE_H = (SCREEN_H / TILE_SIZE) + 2;

static const int MAX_SPAWNS = 16;


class TileMap{
    public:
    TileMap(const char* f, Renderer* r);
    void drawMap();
    void disposeMap();
    //void shiftMap(int x, int y);
    bool isColliding(int x, int y);

    bool scrollX(int x, int cX);
    bool scrollY(int y, int cY);

    int toWorldX(int x) { return x + offsetX; }
    int toWorldY(int y) { return y + offsetY; }
    int toScreenX(int x) { return x - offsetX; }
    int toScreenY(int y) { return y - offsetY; }

    SpawnDef getSpawn() { return spawns[selectedSpawn]; }
    int findSpawn(const char* spawnname);

    void preShift(int x, int y);

    int getOffsetX() { return offsetX; }
    int getOffsetY() { return offsetY; }

    Trigger* getCollidingTrigger(int charX, int charY);

    bool loadMap();

    const char* getBGMFile() { return bgm; }
    const char* getSkyboxFile() { return sky; }

    private:
    bool loadFromFile(const char* file);
    //void parse_textures(FILE* file);
    //void parse_layout(FILE* file);
    //void parse_collision(FILE* file);
    const char* file;
    Renderer* renderer;
    int tiles[64][64];
    CollisionType collision[64][64];
    Entity* entities[64];
    int offsetX = 0;
    int offsetY = 0;
    SpawnDef spawns[16];
    int selectedSpawn = 0;
    char bgm[64];
    char sky[64];


    int skyIndex;
    int skyOffsetX;
    int skyOffsetY;

    int textureAddress = -1;

};