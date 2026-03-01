#include <vgui/button.h>
#include <vgui/UIElement.h>
#include <vgui/text.h>

Button::Button(const char* text, int fti)
{
    t_obj = Text(text, fti, x, y);
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
