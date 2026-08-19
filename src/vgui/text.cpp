#include <cstring>
#include <graphics/renderer.h>
#include <vgui/text.h>

Text::Text()
{
    strcpy(text, "");
    fontTexIndex = SYSTEX_FONT_REG;
    x = 0;
    y = 0;
}

Text::Text(const char* t, int fti, int _x, int _y)
{
    strncpy(text, t, 127);
    fontTexIndex = fti;
    x = _x;
    y = _y;
}

Text::Text(const char* t, int fti)
{
    strncpy(text, t, 127);
    fontTexIndex = fti;
    x = 0;
    y = 0;
}

void Text::move(int x, int y)
{
    this->x = x;
    this->y = y;
}

void Text::SetText(const char *t) {
    strncpy(text, t, 127);
}

void Text::render(Renderer* r)
{
    if (fontTexIndex == -1) return;
    r->drawPlainText(text, x, y, fontTexIndex, fg_r, fg_g, fg_b);
}

void Text::SetFGColor(int r, int g, int b)
{
    fg_r = r;
    fg_g = g;
    fg_b = b;
}