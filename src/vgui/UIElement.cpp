#include <graphics/Renderer.h>
#include <vgui/UIElement.h>

void UIElement::addLowerElement(UIElement* element)
{
    lowerElement = element;
    hasLowerElement = true;
}

void UIElement::addUpperElement(UIElement* element)
{
    upperElement = element;
    hasUpperElement = true;
}

void UIElement::startFocus()
{
    isFocused = true;
}

bool UIElement::giveFocusDown()
{
    if (hasLowerElement){
        isFocused = false;
        lowerElement->startFocus();
        return true;
    }
    return false;
}

bool UIElement::giveFocusUp()
{
    if (hasUpperElement){
        isFocused = false;
        upperElement->startFocus();
        return true;
    }
    return false;
}

void UIElement::move(int x, int y)
{
    this->x = x;
    this->y = y;
}