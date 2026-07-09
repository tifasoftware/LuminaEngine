#pragma once
#include <graphics/Renderer.h>
#include <graphics/Texture.h>

#include "mobile_button.h"

class OnScreenControls {
public:
    OnScreenControls(Renderer* r);
    ~OnScreenControls();
    void draw();

    void OnButtonPress(int tX, int tY, int finger) {
        if (buttonUp->isTouched(tX, tY)) {
            buttonUp->isPressed = true;
            buttonUp->finger = finger;
        }
        if (buttonDown->isTouched(tX, tY)) {
            buttonDown->isPressed = true;
            buttonDown->finger = finger;
        }
        if (buttonLeft->isTouched(tX, tY)) {
            buttonLeft->isPressed = true;
            buttonLeft->finger = finger;
        }
        if (buttonRight->isTouched(tX, tY)) {
            buttonRight->isPressed = true;
            buttonRight->finger = finger;
        }

        if (buttonA->isTouched(tX,tY)) {
            buttonA->isPressed = true;
            buttonA->finger = finger;
        }
        if (buttonB->isTouched(tX,tY)) {
            buttonB->isPressed = true;
            buttonB->finger = finger;
        }
        if (buttonX->isTouched(tX,tY)) {
            buttonX->isPressed = true;
            buttonX->finger = finger;
        }
        if (buttonY->isTouched(tX,tY)) {
            buttonY->isPressed = true;
            buttonY->finger = finger;
        }

        if (buttonMenu->isTouched(tX, tY)) {
            buttonMenu->isPressed = true;
            buttonMenu->finger = finger;
        }
    }

    void OnButtonDepress(int finger) {
        if (buttonUp->finger == finger) {
            buttonUp->isPressed = false;
            buttonUp->finger = -1;
        }
        if (buttonDown->finger == finger) {
            buttonDown->isPressed = false;
            buttonDown->finger = -1;
        }
        if (buttonLeft->finger == finger) {
            buttonLeft->isPressed = false;
            buttonLeft->finger = -1;
        }
        if (buttonRight->finger == finger) {
            buttonRight->isPressed = false;
            buttonRight->finger = -1;
        }

        if (buttonA->finger == finger) {
            buttonA->isPressed = false;
            buttonA->finger = -1;
        }
        if (buttonB->finger == finger) {
            buttonB->isPressed = false;
            buttonB->finger = -1;
        }
        if (buttonX->finger == finger) {
            buttonX->isPressed = false;
            buttonX->finger = -1;
        }
        if (buttonY->finger == finger) {
            buttonY->isPressed = false;
            buttonY->finger = -1;
        }

        if (buttonMenu->finger == finger) {
            buttonMenu->isPressed = false;
            buttonMenu->finger = -1;
        }
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
