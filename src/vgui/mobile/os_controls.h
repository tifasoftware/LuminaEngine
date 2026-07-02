#pragma once
#include <graphics/Renderer.h>
#include <graphics/Texture.h>

class OnScreenControls {
public:
    OnScreenControls(Renderer* r);
    void draw();

private:
    Renderer* renderer;
    int uiIndex1 = -1;
    int uiIndex2 = -1;
};