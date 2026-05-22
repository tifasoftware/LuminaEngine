#pragma once
#include "game/IControllable.h"
#include "graphics/Renderer.h"

class Overlay : public IControllable {
    public:
    Overlay(Renderer* r, IControllable* p);
    void SetParent(IControllable* p) { parent = p; }
    virtual void SetFont(int font) {}
    virtual bool IsFontSet() = 0;
    virtual void draw() = 0;

    bool isComplete() { return completed; }
    bool isEngaged() { return engaged; }

    protected:
    Renderer* renderer;
    IControllable* parent;

    bool completed;
    bool engaged;
};
