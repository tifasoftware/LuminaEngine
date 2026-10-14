#include "counter.h"
#include <graphics/renderer.h>

BatCounter::BatCounter(int atlas, int init_value, int max_value) {
    atlasIndex = atlas;
    value = init_value;
    maxValue = max_value;

    calculateBarFill();
}

void BatCounter::render(Renderer *r) {
    r->fillRect(x + 1, y,barFill,10, barColor);
    r->drawRect(x + 1, y,53,10, ColorA(255,255,255,255));
    drawNumber(r, value, x + 2, y + 1);

    //drawSlash(r, x + 24, y);
    //drawNumber(r, maxValue, x + 32, y);
}

void BatCounter::drawNumber(Renderer *r, int val, int x, int y) {
    int dx = x;
    if (val > 10000) val = 9999;

    if (val < 1000) {
        //drawDigit(r,0,x,y);
    } else {
        drawDigit(r, val / 1000, dx, y);
        dx += 8;

        if (val % 1000 < 100) {
            drawDigit(r,0,dx,y);
            dx += 8;
        }

        val = val % 1000;
    }

    if (val < 100) {
        //drawDigit(r,0, dx, y);
    } else {
        drawDigit(r, val / 100, dx, y);
        dx += 8;

        if (val % 100 < 10) {
            drawDigit(r,0,dx,y);
            dx += 8;
        }

        val = val % 100;
    }

    if (val < 10) {
        //drawDigit(r, 0, dx, y);
    } else {
        drawDigit(r, val / 10, dx, y);
        val = val % 10;
        dx += 8;
    }

    drawDigit(r, val, dx, y);
}

void BatCounter::drawDigit(Renderer *r, uint8_t val, int x, int y) {
    uint8_t cX = 0;
    uint8_t cY = 0;

    if (val > 9) {
        return;
    }

    if (val > 7) {
        cY += 8;
        cX = (val - 8) * 8;
    } else {
        cX = val * 8;
    }

    r->drawSubSprite(atlasIndex, x, y, cX, cY, 8, 8);
}

void BatCounter::drawSlash(Renderer *r, int x, int y) {
    r->drawSubSprite(atlasIndex, x, y, 16, 8, 8, 8);
}

void BatCounter::calculateBarFill() {
    float val = static_cast<float>(value);
    float mV = static_cast<float>(maxValue);

    float bF = (val / mV) * 53.0f;

    barFill = static_cast<int>(bF);
}
