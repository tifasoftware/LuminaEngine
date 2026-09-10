#pragma once
#include "counter.h"
#include "vgui/glyph.h"
#include "vgui/imagebox.h"
#include "vgui/text.h"
#include "vgui/UIElement.h"

class CharacterCard : public UIElement {
public:
    CharacterCard(int battleGlyphIndex, int charImageIndex, const char* charName);
    void move(int x, int y) override;
    void render(Renderer *r) override;
    void destroy() override;

private:
    Glyph* glyph_hp;
    Glyph* glyph_mp;
    ImageBox* imgbox;
    Text* charText;

    BatCounter* hp_counter;
    BatCounter* mp_counter;


};
