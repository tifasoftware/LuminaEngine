#pragma once

#include <graphics/Renderer.h>

class Text
{
    public:
    Text(const char* t, int fti, int _x, int _y);
    Text(const char* t, int fti);
    ~Text();
    Text();
    void SetFGColor(int r, int g, int b);
    void Render(Renderer* r);
    void Move(int x, int y);

    private:
    const char* text;
    int fontTexIndex = -1;
    int fg_r = 200;
    int fg_g = 200;
    int fg_b = 200;

    int x = 0;
    int y = 0;
};