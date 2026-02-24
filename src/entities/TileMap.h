#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <cstdio>
#include <cstring>
#include <graphics/Renderer.h>

//PSP Resolution Width - 480
//PSP Resolution Height - 272
static const int SCREEN_W = 480;
static const int SCREEN_H = 272;

static const int TILE_SIZE = 16;

static const int TILE_W = SCREEN_W / TILE_SIZE;
static const int TILE_H = SCREEN_H / TILE_SIZE;


class TileMap{
    public:
    TileMap(const char* file, Renderer* r);
    void drawMap();
    void disposeMap();

    private:
    bool loadFromFile(const char* file);
    void parse_textures(FILE* file);
    void parse_layout(FILE* file);
    Renderer* renderer;
    int tiles[TILE_W][TILE_H];
};