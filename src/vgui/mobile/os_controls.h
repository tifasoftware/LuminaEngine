#pragma once
#include <graphics/Renderer.h>
#include <graphics/Texture.h>

#include "mobile_button.h"

class OnScreenControls {
public:
    OnScreenControls(Renderer* r);
    ~OnScreenControls();
    void draw() { draw(0); }
    void draw(int pressedBtns);

    int GetPressedButtons(int tX, int tY);

private:
    static const int OSC_TILE_SIZE = 48;

    Renderer* renderer;

    MobileButton* buttonUp;
    MobileButton* buttonDown;
    MobileButton* buttonLeft;
    MobileButton* buttonRight;

    MobileButton* buttonA;
    MobileButton* buttonB;
    MobileButton* buttonX;
    MobileButton* buttonY;

    MobileButton* buttonMenu;
};
