#include <cstring>
#include <graphics/renderer.h>
#include <vgui/text.h>

Text::Text()
{
    strcpy(text, "");
    fontTexIndex = SYSTEX_FONT_REG;
    x = 0;
    y = 0;

    fg.r = 200;
    fg.g = 200;
    fg.b = 200;

    textSet = false;
    compiled_ltl = CompiledLTL();
}

Text::Text(const char* t, int fti, int _x, int _y)
{
    strncpy(text, t, 255);
    fontTexIndex = fti;
    x = _x;
    y = _y;

    fg.r = 200;
    fg.g = 200;
    fg.b = 200;

    textSet = true;
    compiled_ltl = CompiledLTL();
    compile();
}

Text::Text(const char* t, int fti)
{
    strncpy(text, t, 255);
    fontTexIndex = fti;
    x = 0;
    y = 0;

    fg.r = 200;
    fg.g = 200;
    fg.b = 200;

    textSet = true;
    compiled_ltl = CompiledLTL();
    compile();
}

void Text::move(int x, int y)
{
    this->x = x;
    this->y = y;
}

void Text::SetText(const char *t) {
    strncpy(text, t, 255);
    textSet = true;
    compile();
}

void Text::render(Renderer* r)
{
    if (fontTexIndex == -1) return;
    //r->drawPlainText(text, x, y, fontTexIndex, fg.r, fg.g, fg.b);
    r->drawLTLText(&compiled_ltl, fontTexIndex, x, y);
}

void Text::SetFGColor(int r, int g, int b)
{
    fg.r = r;
    fg.g = g;
    fg.b = b;

    compile();
}

void Text::compile() {
    if (textSet) {
        CompiledLTL::compile_string(&compiled_ltl, text, fg);
    }
}
