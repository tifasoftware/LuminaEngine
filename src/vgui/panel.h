#pragma once

#include <graphics/Renderer.h>
#include <vgui/UIElement.h>

static const int MAX_ELEMENTS = 16;

class Panel
{
    public:
    Panel(Renderer* r, int x, int y, int w, int h);
    Panel(Renderer* r, int w, int h);
    void Render();
    void setBGColor(int r, int g, int b);
    void setFGColor(int r, int g, int b);
    int addElement(UIElement* element);
    void destroy();

    int getX() const { return x; }
    int getY() const { return y; }
    int getW() const { return w; }
    int getH() const { return h; }

    private:
    Renderer* renderer;

    void populateArray();

    int x = 0;
    int y = 0;
    int w = 0;
    int h = 0;

    int bg_r = 86;
    int bg_g = 32;
    int bg_b = 81;

    int fg_r = 200;
    int fg_g = 200;
    int fg_b = 200;

    UIElement* elements[MAX_ELEMENTS];
    int elementCount = 0;
};