#pragma once
#include <cstdint>

#include "os_controls.h"
#include "graphics/renderer.h"

class MobileButton {
public:
    MobileButton(int x, int y, int w, int h, int tI, int tOX, int tOY) {
        this->x = x;
        this->y = y;
        this->w = w;
        this->h = h;
        this->texIndex = tI;
        this->texOffsetX = tOX;
        this->texOffsetY = tOY;
    }

    uint16_t x, y, w, h;

    bool isPressed = false;
    int finger = -1;

    bool isTouched(int tX, int tY) {
        if ((tX <= (x+w)) && (tX >= x) && (tY <= (y+h)) && (tY >= y)) return true;
        return false;
    }

    void drawButton(Renderer* r) {
        drawButton(r, false);
    }

    void drawButton(Renderer* r, int tX, int tY) {
        drawButton(r, isTouched(tX, tY));
    }

    void drawButton(Renderer* r, bool touched) {
        SDL_SetRenderDrawBlendMode(r->getRenderer(), SDL_BLENDMODE_BLEND);
        r->getTexture(texIndex)->SetOpacity(127);

        r->drawSubSprite(texIndex, x, y,texOffsetX + getBooleanOffset(touched),texOffsetY, w,h);

        r->getTexture(texIndex)->SetOpacity();
        SDL_SetRenderDrawBlendMode(r->getRenderer(), SDL_BLENDMODE_NONE);
    }

    int getBooleanOffset(bool cond) {
        if (cond) return w;
        return 0;
    }

private:
    int texIndex = -1;
    int texOffsetX = 0;
    int texOffsetY = 0;
};
