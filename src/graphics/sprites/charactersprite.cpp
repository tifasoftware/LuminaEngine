#include "charactersprite.h"

void CharacterSprite::draw(int x, int y, int mx, int my, Renderer* r) {
    if (mx > 0) dirIndex = 3;
    if (mx < 0) dirIndex = 2;
    if (my > 0) dirIndex = 0;
    if (my < 0) dirIndex = 1;

    if (mx == 0 && my == 0) animIndex = 1;

    r->drawSubSprite(textureIndex,
        x - (spriteW / 2),
        y - (spriteW / 2),
        (dirIndex * spriteW),
        (animIndex * spriteH),
        spriteH, spriteH);
}

void CharacterSprite::animate(int framerate, int mx, int my) {
    if (mx == 0 && my == 0) return;
    float timeline = ((1.0f * frame) / (1.0f * framerate));
    animIndex = 4 * timeline;
    frame++;
    if (frame >= framerate)
    {
        frame = 0;
    }
}