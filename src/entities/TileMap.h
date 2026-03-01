#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <cstdio>
#include <cstring>
#include <graphics/Renderer.h>
#include <formats/lmap.h>

//PSP Resolution Width - 480
//PSP Resolution Height - 272
static const int SCREEN_W = 480;
static const int SCREEN_H = 272;

static const int TILE_SIZE = 16;

static const int TILE_W = (SCREEN_W / TILE_SIZE) + 2;
static const int TILE_H = (SCREEN_H / TILE_SIZE) + 2;


class TileMap{
    public:
    TileMap(const char* f, Renderer* r);
    void drawMap();
    void disposeMap();
    void shiftMap(int x, int y);
    bool isColliding(int x, int y);
    bool loadMap();

    private:
    bool loadFromFile(const char* file);
    //void parse_textures(FILE* file);
    //void parse_layout(FILE* file);
    //void parse_collision(FILE* file);
    const char* file;
    Renderer* renderer;
    int tiles[64][64];
    //int collision[TILE_W][TILE_H];
    int offsetX = 0;
    int offsetY = 0;

    int textureAddress = -1;

};