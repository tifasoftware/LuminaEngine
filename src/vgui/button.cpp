#include <vgui/button.h>
#include <vgui/UIElement.h>
#include <vgui/text.h>

Button::Button(const char* text, const char* tag, int fti)
{
    t_obj = Text(text, fti, x, y);
    this->tag = tag;
    deSelect();
}

void Button::render(Renderer* r)
{
    t_obj.Render(r);
}

void Button::move(int x, int y)
{
    UIElement::move(x,y);
    t_obj.Move(x, y);
}

void Button::startFocus()
{
    UIElement::startFocus();

    t_obj.SetFGColor(255, 255, 255);
}

bool Button::giveFocusDown()
{
    bool pr = UIElement::giveFocusDown();

    if (!isFocused) deSelect();

    return pr;
}

bool Button::giveFocusUp()
{
    bool pr = UIElement::giveFocusUp();

    if (!isFocused) deSelect();

    return pr;
}

void Button::deSelect()
{
    t_obj.SetFGColor(200, 200, 200);
}
