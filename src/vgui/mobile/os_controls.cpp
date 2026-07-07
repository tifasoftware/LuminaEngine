#include "os_controls.h"

OnScreenControls::OnScreenControls(Renderer* r) {
    renderer = r;

    // D-Pad
    buttonUp = new MobileButton(56, r->GetHeight() - 152,
        OSC_TILE_SIZE, OSC_TILE_SIZE,
        SYSTEX_OSC_BTNS,
        0, 0);

    buttonDown = new MobileButton(56, r->GetHeight() - 56,
        OSC_TILE_SIZE, OSC_TILE_SIZE,
        SYSTEX_OSC_BTNS,
        0, OSC_TILE_SIZE);

    buttonLeft = new MobileButton(8, r->GetHeight() - 104,
        OSC_TILE_SIZE, OSC_TILE_SIZE,
        SYSTEX_OSC_BTNS,
        0, OSC_TILE_SIZE * 2);

    buttonRight = new MobileButton(104, r->GetHeight() - 104,
        OSC_TILE_SIZE, OSC_TILE_SIZE,
        SYSTEX_OSC_BTNS,
        0, OSC_TILE_SIZE * 3);


    //Action Buttons

    buttonA = new MobileButton(r->GetWidth() - 104, r->GetHeight() - 56,
        OSC_TILE_SIZE, OSC_TILE_SIZE,
        SYSTEX_OSC_BTNS,
        OSC_TILE_SIZE * 2, 0);

    buttonB = new MobileButton(r->GetWidth() - 56, r->GetHeight() - 104,
        OSC_TILE_SIZE, OSC_TILE_SIZE,
        SYSTEX_OSC_BTNS,
        OSC_TILE_SIZE * 2, OSC_TILE_SIZE);

    buttonX = new MobileButton(r->GetWidth() - 152, r->GetHeight() - 104,
        OSC_TILE_SIZE, OSC_TILE_SIZE,
        SYSTEX_OSC_BTNS,
        OSC_TILE_SIZE * 2, OSC_TILE_SIZE * 2);

    buttonY = new MobileButton((r->GetWidth() - 104), r->GetHeight() - 152,
        OSC_TILE_SIZE, OSC_TILE_SIZE,
        SYSTEX_OSC_BTNS,
        OSC_TILE_SIZE * 2, OSC_TILE_SIZE * 3);

    // Menu Button

    buttonMenu = new MobileButton(8, 8,
        OSC_TILE_SIZE, OSC_TILE_SIZE,
        SYSTEX_OSC_MENU,
        0, 0);
}

void OnScreenControls::draw(int pressedBtns) {

    buttonUp->drawButton(renderer, (pressedBtns & 1) != 0);
    buttonDown->drawButton(renderer, (pressedBtns & 2) != 0);
    buttonLeft->drawButton(renderer, (pressedBtns & 4) != 0);
    buttonRight->drawButton(renderer, (pressedBtns & 8) != 0);

    buttonA->drawButton(renderer, (pressedBtns & 16) != 0);
    buttonB->drawButton(renderer, (pressedBtns & 32) != 0);
    buttonX->drawButton(renderer, (pressedBtns & 64) != 0);
    buttonY->drawButton(renderer, (pressedBtns & 128) != 0);

    buttonMenu->drawButton(renderer, (pressedBtns & 256) != 0);
}

OnScreenControls::~OnScreenControls() {
    delete buttonA;
    delete buttonB;
    delete buttonX;
    delete buttonY;

    delete buttonUp;
    delete buttonDown;
    delete buttonLeft;
    delete buttonRight;

    delete buttonMenu;
}

int OnScreenControls::GetPressedButtons(int tX, int tY) {
    int r = 0;

    if (buttonUp->isTouched(tX, tY)) r += 1;
    if (buttonDown->isTouched(tX, tY)) r += 2;
    if (buttonLeft->isTouched(tX, tY)) r += 4;
    if (buttonRight->isTouched(tX, tY)) r += 8;
    if (buttonA->isTouched(tX, tY)) r += 16;
    if (buttonB->isTouched(tX, tY)) r += 32;
    if (buttonX->isTouched(tX, tY)) r += 64;
    if (buttonY->isTouched(tX, tY)) r += 128;
    if (buttonMenu->isTouched(tX, tY)) r += 256;

    return r;
}
