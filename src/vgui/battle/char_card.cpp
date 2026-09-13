#include "char_card.h"

CharacterCard::CharacterCard(int battleGlyphIndex, int charImageIndex, const char* charName) {
    // Create Glyphs

    glyph_hp = new Glyph();
    glyph_hp->setAtlas(battleGlyphIndex);
    glyph_hp->setGlyph(16, 16, 16, 8);

    glyph_mp = new Glyph();
    glyph_mp->setAtlas(battleGlyphIndex);
    glyph_mp->setGlyph(16, 24, 16, 8);

    // Create ImageBox
    imgbox = new ImageBox();
    imgbox->setTexture(charImageIndex);

    // Create Name Text
    charText = new Text(charName, SYSTEX_FONT_REG);

    // Create Battle Counters
    hp_counter = new BatCounter(battleGlyphIndex, 100,300);
    mp_counter = new BatCounter(battleGlyphIndex, 12,30);
}

void CharacterCard::move(int x, int y) {
    this->x = x;
    this->y = y;

    charText->move(x + 2,y + 0);
    imgbox->move(x + 2,y + 18);

    glyph_hp->move(x + 0, y + 88);
    glyph_mp->move(x + 0, y + 98);
    hp_counter->move(x + 12, y + 88);
    mp_counter->move(x + 12, y + 98);
}

void CharacterCard::render(Renderer *r) {
    if (highlight) {
        r->fillRect(x, y, 68, 106, ColorA(94, 62,82, 255));
        r->drawRect(x, y, 68, 106, ColorA(255,255,255,255));
    }

    imgbox->render(r);
    charText->render(r);

    glyph_hp->render(r);
    glyph_mp->render(r);
    hp_counter->render(r);
    mp_counter->render(r);
}

void CharacterCard::destroy() {
    delete glyph_hp;
    delete glyph_mp;
    delete imgbox;
    delete hp_counter;
    delete mp_counter;
    delete charText;
}
