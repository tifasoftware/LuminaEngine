#pragma once

#include <graphics/Renderer.h>

class UIElement
{
    public:
    virtual void render(Renderer* r) = 0;
    virtual void destroy() = 0;

    virtual ~UIElement() {}
};