#pragma once

#include <graphics/renderer.h>

#include "UIElement.h"

class Text : public UIElement
{
public:
    Text(const char* t, int fti, int _x, int _y);
    Text(const char* t, int fti);
    ~Text() override {}
    Text();
    void SetFGColor(int r, int g, int b);
    void SetText(const char* t);
    void SetFont(int fti) { fontTexIndex = fti; }
    void render(Renderer* r) override;
    void destroy() override {}

    bool isFontSet() { return fontTexIndex != -1; }

private:
    char text[128];
    int fontTexIndex = SYSTEX_FONT_REG;
    int fg_r = 200;
    int fg_g = 200;
    int fg_b = 200;

    //int x = 0;
    //int y = 0;
};