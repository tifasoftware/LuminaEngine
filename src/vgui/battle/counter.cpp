#include "counter.h"
#include <graphics/renderer.h>

BatCounter::BatCounter(int atlas, int init_value, int max_value) {
    atlasIndex = atlas;
    value = init_value;
    maxValue = max_value;
}

void BatCounter::render(Renderer *r) {
    drawNumber(r, value, x, y);
    drawSlash(r, x + 24, y);
    drawNumber(r, maxValue, x + 32, y);
}

void BatCounter::drawNumber(Renderer *r, int val, int x, int y) {
    if (val > 1000) val = 999;

    if (val < 100) {
        drawDigit(r,0, x, y);
    } else {
        drawDigit(r, val / 100, x, y);
        val = val % 100;
    }

    if (val < 10) {
        drawDigit(r, 0, x + 8, y);
    } else {
        drawDigit(r, val / 10, x + 8, y);
        val = val % 10;
    }

    drawDigit(r, val, x + 16, y);
}

void BatCounter::drawDigit(Renderer *r, uint8_t val, int x, int y) {
    uint8_t cX = 0;
    uint8_t cY = 0;

    if (val > 9) {
        return;
    }

    if (val > 7) {
        cY += 8;
        cX = (val - 7) * 8;
    } else {
        cX = val * 8;
    }

    r->drawSubSprite(atlasIndex, x, y, cX, cY, 8, 8);
}

void BatCounter::drawSlash(Renderer *r, int x, int y) {
    r->drawSubSprite(atlasIndex, x, y, 16, 8, 8, 8);
}
