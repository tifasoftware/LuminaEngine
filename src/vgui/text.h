#pragma once

#include <graphics/Renderer.h>

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
    void move(int x, int y) override;
    void destroy() override {}

    bool isFontSet() { return fontTexIndex != -1; }

    private:
    char text[128];
    int fontTexIndex = -1;
    int fg_r = 200;
    int fg_g = 200;
    int fg_b = 200;

    int x = 0;
    int y = 0;
};
