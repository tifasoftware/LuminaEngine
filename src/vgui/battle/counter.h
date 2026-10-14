#pragma once
#include "vgui/UIElement.h"

class BatCounter : public UIElement {
public:
    BatCounter(int atlas) { BatCounter(atlas, 0, 0); }
    BatCounter(int atlas, int init_value, int max_value);

    void render(Renderer *r) override;
    void setValue(int v) { value = v; calculateBarFill(); }
    void setMaxValue(int v) { maxValue = v; calculateBarFill(); }

    void setBarColor(ColorA ca) { barColor = ca; }

    //No Ops
    void destroy() override {}

private:
    void drawNumber(Renderer *r, int val, int x, int y);
    void drawDigit(Renderer *r, uint8_t val, int x, int y);
    void drawSlash(Renderer *r, int x, int y);

    void calculateBarFill();

    ColorA barColor = ColorA(30,100,40,255);

    int barFill = 53;
    int atlasIndex = -1;
    int value = 0;
    int maxValue = 0;
};
