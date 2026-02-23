#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <cstdio>
#include <cstring>
#include <graphics/Renderer.h>

//PSP Resolution Width - 480
//PSP Resolution Height - 272
static const int tileW = 30;
static const int tileH = 17;
static const int tileSize = 16;

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
    int tiles[tileW][tileH];
};