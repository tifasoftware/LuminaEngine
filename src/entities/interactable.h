#pragma once
#include "entity.h"
#include "graphics/Renderer.h"

class Interactable : public Entity {
    public:
    virtual void render(Renderer* r) = 0;
    virtual void interact() = 0;

    bool willCharacterInteract();

    ~Interactable();


};
