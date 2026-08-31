#pragma once
#include "vgui/UIElement.h"

class BatCounter : public UIElement {
public:
    BatCounter(int atlas) { BatCounter(atlas, 0, 0); }
    BatCounter(int atlas, int init_value, int max_value);

    void render(Renderer *r) override;

    //No Ops
    void destroy() override {}

private:
    void drawNumber(Renderer *r, int val, int x, int y);
    void drawDigit(Renderer *r, uint8_t val, int x, int y);
    void drawSlash(Renderer *r, int x, int y);

    int atlasIndex = -1;
    int value = 0;
    int maxValue = 0;
};
