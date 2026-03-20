#include "sprite.h"

void Sprite::animate(int framerate, int mx, int my) {
    //No need for animation on a vanilla sprite
}

void Sprite::draw(int x, int y, int mx, int my, Renderer* r) {
    r->drawSprite(textureIndex, x, y);
}

void Sprite::draw(int x, int y, Renderer* r) {
    draw(x, y, 0, 0, r);
}
