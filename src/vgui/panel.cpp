#include <vgui/panel.h>

Panel::Panel(Renderer* r, int x, int y, int w, int h)
{
    renderer = r;
    this->x = x;
    this->y = y;
    this->w = w;
    this->h = h;

    populateArray();
}

Panel::Panel(Renderer* r, int w, int h)
{
    renderer = r;
    this->x = (480 / 2) - (w / 2);
    this->y = (272 / 2) - (h / 2);
    this->w = w;
    this->h = h;

    populateArray();
}

void Panel::populateArray()
{
    for (int i = 0; i < MAX_ELEMENTS; i++)
    {
        elements[i] = nullptr;
    }
}

void Panel::Render()
{
    SDL_Renderer* r = renderer->getRenderer();
    SDL_SetRenderDrawColor(r, bg_r, bg_g, bg_b, 200);
    SDL_SetRenderDrawBlendMode(r, SDL_BLENDMODE_BLEND);
    SDL_Rect box = {x, y, w, h};
    SDL_RenderFillRect(r, &box);

    SDL_SetRenderDrawColor(r, fg_r, fg_g, fg_b, 255);
    SDL_RenderDrawRect(r, &box);

    for (int i = 0; i < MAX_ELEMENTS; i++)
    {
        if (elements[i] != nullptr)
            elements[i]->render(renderer);
    }
}

void Panel::setBGColor(int r, int g, int b)
{
    bg_r = r;
    bg_g = g;
    bg_b = b;
}

void Panel::setFGColor(int r, int g, int b)
{
    fg_r = r;
    fg_g = g;
    fg_b = b;
}

int Panel::addElement(UIElement* element, int x, int y)
{
    int eX = x + getX();
    int eY = y + getY();
    element->move(eX, eY);
    elements[elementCount] = element;
    return elementCount++;
}

void Panel::destroy()
{
    for (int i = 0; i < MAX_ELEMENTS; i++)
    {
        if (elements[i] != nullptr)
        {
            delete elements[i];
            elements[i] = nullptr;
        }
    }
}