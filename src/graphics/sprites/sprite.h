#pragma once
#include "graphics/Renderer.h"

class Sprite {
    public:
    Sprite(int ti) { textureIndex = ti; spriteW = 16; spriteH = 16; }
    Sprite(int ti, int w, int h) {textureIndex = ti; spriteW=w; spriteH=h;}
    virtual ~Sprite() = default;

    virtual void draw(int x, int y, int mx, int my, Renderer* r);
    virtual void draw(int x, int y, Renderer* r);
    virtual void animate(int framerate, int mx, int my);

    protected:
    int textureIndex = -1;
    int spriteW, spriteH = 16;
};
