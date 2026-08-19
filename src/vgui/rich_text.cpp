#include <cstring>
#include <graphics/renderer.h>
#include <vgui/rich_text.h>

RichText::RichText()
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

RichText::RichText(const char* t, int fti, int _x, int _y)
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

RichText::RichText(const char* t, int fti)
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

void RichText::move(int x, int y)
{
    this->x = x;
    this->y = y;
}

void RichText::SetText(const char *t) {
    strncpy(text, t, 255);
    textSet = true;
    compile();
}

void RichText::render(Renderer* r)
{
    if (fontTexIndex == -1) return;
    r->drawLTLText(&compiled_ltl, fontTexIndex, x, y, 0, trim);
}

void RichText::SetFGColor(int r, int g, int b)
{
    fg.r = r;
    fg.g = g;
    fg.b = b;

    compile();
}

void RichText::compile() {
    if (textSet) {
        CompiledLTL::compile_string(&compiled_ltl, text, fg);
    }
}

int RichText::GetTextLength() {
    return compiled_ltl.GetPrintableLength();
}
