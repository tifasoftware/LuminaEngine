#pragma once
#include "sprite.h"

class CharacterSprite : public Sprite {
    public:
    CharacterSprite(int ti) : Sprite(ti) {
        textureIndex = ti;
        spriteH = 32;
        spriteW = 32;
    }

    CharacterSprite(int ti, int w, int h) : Sprite(ti, w, h) {
        textureIndex = ti;
        spriteH = h;
        spriteW = w;
    }

    void draw(int x, int y, int mx, int my, Renderer* r) override;
    void animate(int framerate, int mx, int my) override;

    private:
    int dirIndex = 0;
    int animIndex = 0;
    int frame = 0;
};
