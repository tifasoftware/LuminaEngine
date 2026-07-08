#pragma once
#include <graphics/Renderer.h>
#include <graphics/Texture.h>

#include "mobile_button.h"

class OnScreenControls {
public:
    OnScreenControls(Renderer* r);
    ~OnScreenControls();
    void draw();

    void OnButtonPress(int tX, int tY) {
        if (buttonUp->isTouched(tX, tY)) buttonUp->isPressed = true;
        if (buttonDown->isTouched(tX, tY)) buttonDown->isPressed = true;
        if (buttonLeft->isTouched(tX, tY)) buttonLeft->isPressed = true;
        if (buttonRight->isTouched(tX, tY)) buttonRight->isPressed = true;

        if (buttonA->isTouched(tX,tY)) buttonA->isPressed = true;
        if (buttonB->isTouched(tX,tY)) buttonB->isPressed = true;
        if (buttonX->isTouched(tX,tY)) buttonX->isPressed = true;
        if (buttonY->isTouched(tX,tY)) buttonY->isPressed = true;

        if (buttonMenu->isTouched(tX, tY)) buttonMenu->isPressed = true;
    }

    void OnButtonDepress(int tX, int tY) {
        if (buttonUp->isTouched(tX, tY)) buttonUp->isPressed = false;
        if (buttonDown->isTouched(tX, tY)) buttonDown->isPressed = false;
        if (buttonLeft->isTouched(tX, tY)) buttonLeft->isPressed = false;
        if (buttonRight->isTouched(tX, tY)) buttonRight->isPressed = false;

        if (buttonA->isTouched(tX,tY)) buttonA->isPressed = false;
        if (buttonB->isTouched(tX,tY)) buttonB->isPressed = false;
        if (buttonX->isTouched(tX,tY)) buttonX->isPressed = false;
        if (buttonY->isTouched(tX,tY)) buttonY->isPressed = false;

        if (buttonMenu->isTouched(tX, tY)) buttonMenu->isPressed = false;
    }

    int GetPressedButtons();

private:
    static const int OSC_TILE_SIZE = 48;

    int pressedBtns = 0;

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
