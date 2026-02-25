#pragma once

#include <graphics/Renderer.h>

class UIElement
{
    public:
    virtual void render(Renderer* r) = 0;
    virtual void destroy() = 0;
    void addUpperElement(UIElement* element);
    void addLowerElement(UIElement* element);
    void giveFocusUp();
    void giveFocusDown();
    void startFocus();

    virtual ~UIElement() {}

    private:
    int x = 0;
    int y = 0;
    bool isFocused = false;
    bool hasUpperElement = false;
    bool hasLowerElement = false;
    UIElement* upperElement;
    UIElement* lowerElement;
};