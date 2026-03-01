#pragma once

#include <graphics/Renderer.h>

class UIElement
{
    public:
    virtual void render(Renderer* r) = 0;
    virtual void destroy() = 0;
    void addUpperElement(UIElement* element);
    void addLowerElement(UIElement* element);
    virtual void move(int x, int y);
    virtual void giveFocusUp();
    virtual void giveFocusDown();
    virtual void startFocus();
    bool IsFocused() { return isFocused; }

    virtual ~UIElement() {}

    protected:
    int x = 0;
    int y = 0;
    bool isFocused = false;
    bool hasUpperElement = false;
    bool hasLowerElement = false;
    UIElement* upperElement;
    UIElement* lowerElement;
};