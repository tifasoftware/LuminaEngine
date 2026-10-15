#pragma once
#include "vgui/UIElement.h"

class BatCounter : public UIElement {
public:
    BatCounter(int atlas) { BatCounter(atlas, 0, 0); }
    BatCounter(int atlas, int init_value, int max_value);

    void render(Renderer *r) override;
    void setValue(int v) { value = v; calculateBarFill(); }
    void slideValue(int v, uint8_t frames);
    void setMaxValue(int v) { maxValue = v; calculateBarFill(); }

    void setBarColor(ColorA ca) { barColor = ca; }

    //No Ops
    void destroy() override {}

    void animate();
    void cancelAnimation();
    bool inAnimation() { return newValue != -1; }

private:
    void drawNumber(Renderer *r, int val, int x, int y);
    void drawDigit(Renderer *r, uint8_t val, int x, int y);
    void drawSlash(Renderer *r, int x, int y);

    void calculateBarFill();

    ColorA barColor = ColorA(30,100,40,255);

    uint8_t barFill = 53;
    int atlasIndex = -1;
    int value = 0;
    int maxValue = 0;

    int newValue = -1;
    uint8_t frame = 0;
    uint8_t frameSkips = 0;
    uint8_t delta = 0;
};
