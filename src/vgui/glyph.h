#pragma once
#include "UIElement.h"

class Glyph : public UIElement {
public:
    void render(Renderer *r) override { if (texIndex != -1) r->drawSubSprite(texIndex, x, y, cX, cY, cW, cH); }
    void destroy() override {}
    //void move(int x, int y) override { this->x = x; this->y = y; }
    bool giveFocusUp() override { return false; }
    bool giveFocusDown() override { return false; }
    void startFocus() override {}
    void setAtlas(int t) { texIndex = t; }
    void setAtlas() { texIndex = -1; }

    void setGlyph(int _x, int _y, int _w, int _h) {
        cX = _x;
        cY = _y;
        cW = _w;
        cH = _h;
    }

    void setGlyph(int _x, int _y, int _s) { setGlyph(_x, _y, _s, _s); }

    int getAtlas() { return texIndex; }

    ~Glyph() override {}
    Glyph() {}

protected:
    int texIndex = -1;
    int cX = 0;
    int cY = 0;
    int cW = 8;
    int cH = 8;
};