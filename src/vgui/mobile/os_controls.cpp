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

void OnScreenControls::draw() {

    buttonUp->drawButton(renderer, buttonUp->isPressed);
    buttonDown->drawButton(renderer, buttonDown->isPressed);
    buttonLeft->drawButton(renderer, buttonLeft->isPressed);
    buttonRight->drawButton(renderer, buttonRight->isPressed);

    buttonA->drawButton(renderer, buttonA->isPressed);
    buttonB->drawButton(renderer, buttonB->isPressed);
    buttonX->drawButton(renderer, buttonX->isPressed);
    buttonY->drawButton(renderer, buttonY->isPressed);

    buttonMenu->drawButton(renderer, buttonMenu->isPressed);
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

int OnScreenControls::GetPressedButtons() {
    int r = 0;

    if (buttonUp->isPressed) r += 1;
    if (buttonDown->isPressed) r += 2;
    if (buttonLeft->isPressed) r += 4;
    if (buttonRight->isPressed) r += 8;
    if (buttonA->isPressed) r += 16;
    if (buttonB->isPressed) r += 32;
    if (buttonX->isPressed) r += 64;
    if (buttonY->isPressed) r += 128;
    if (buttonMenu->isPressed) r += 256;

    return r;
}
