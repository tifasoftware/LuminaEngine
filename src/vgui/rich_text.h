#pragma once

#include <graphics/renderer.h>

#include "UIElement.h"

class RichText : public UIElement
{
    public:
    RichText(const char* t, int fti, int _x, int _y);
    RichText(const char* t, int fti);
    ~RichText() override {}
    RichText();
    void SetFGColor(int r, int g, int b);
    void SetText(const char* t);
    void SetFont(int fti) { fontTexIndex = fti; compile(); }
    void render(Renderer* r) override;
    void move(int x, int y) override;
    void destroy() override {}

    void SetTrim(int t) { trim = t; }
    void IncrementTrim() { trim++; }

    int GetTextLength();

    bool isFontSet() { return fontTexIndex != -1; }

    private:
    char text[256];
    CompiledLTL compiled_ltl;

    bool textSet;
    void compile();

    int fontTexIndex = SYSTEX_FONT_REG;
    Color fg;

    int x = 0;
    int y = 0;

    int trim = -1;
};
