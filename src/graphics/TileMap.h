#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <graphics/Renderer.h>

//PSP Resolution Width - 480
//PSP Resolution Height - 272
static const int tileW = 30;
static const int tileH = 17;
static const int tileSize = 16;

class TileMap{
    public:
    TileMap(Renderer* r);
    void drawMap();

    private:
    Renderer* renderer;
};