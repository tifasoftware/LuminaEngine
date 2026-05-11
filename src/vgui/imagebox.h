#pragma once
#include "UIElement.h"

class ImageBox : public UIElement {
    public:
    void render(Renderer *r) override { if (texIndex != -1) r->drawSprite(texIndex, x, y); }
    void destroy() override {}
    void move(int x, int y) override { this->x = x; this->y = y; }
    bool giveFocusUp() override { return false; }
    bool giveFocusDown() override { return false; }
    void startFocus() override {}
    void setTexture(int t) { texIndex = t; }
    void setTexture() { texIndex = -1; }
    int getTexture() { return texIndex; }

    ~ImageBox() override {}
    ImageBox() {}

    protected:
    int texIndex = -1;
};
