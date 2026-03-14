#pragma once
#include "graphics/Renderer.h"

class Interactable {
    public:
    virtual void render(Renderer* r) = 0;
    virtual void interact() = 0;

    bool willCharacterInteract();

    ~Interactable();

    protected:
    int x;
    int y;
    int w;
    int h;
};
