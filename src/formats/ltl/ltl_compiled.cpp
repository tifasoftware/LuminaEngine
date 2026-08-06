#include "ltl.h"

CompiledLTL::CompiledLTL(int length, int styles) {
    lucii_string = new uint8_t[length];
    font_table = new uint8_t[styles];
    color_table = new Color[styles];
}

CompiledLTL::~CompiledLTL() {
    delete lucii_string;
    delete font_table;
    delete color_table;
}

Color CompiledLTL::getColor(int index) {
    int style = lucii_string[index];
    return color_table[style];
}

int CompiledLTL::getFont(int index) {
    int style = lucii_string[index];
    return font_table[style];
}

CompiledLTL* CompiledLTL::compile_string(const char *raw_ltl, Color defaultColor) {
    CompiledLTL* result = new CompiledLTL(128, 30);

    int font = 0;
    Color color = Color();
    bool applyColor = false;
    LTLParser parser;

    int lchar = 0;
    int lstyle = 0;

    parser.parseString(raw_ltl);

    while (parser.advance()) {
        bool applyNewStyle = false;
        char c = parser.nextChar();

        if (color != parser.nextColor()) {
            applyNewStyle = true;
            color = parser.nextColor();
        }

        if (applyColor != parser.nextApplyColor()) {
            applyColor = parser.nextApplyColor();
            applyNewStyle = true;

            if (applyColor) {
                result->setColor(lstyle, color);

            } else {
                result->setColor(lchar, defaultColor);
            }
        }

        if (font != parser.nextFont()) {
            font = parser.nextFont();
            applyNewStyle = true;

            result->setFont(lstyle, font);
        }

        if (applyNewStyle) {
            result->set(lchar, lstyle);
            lchar++;
            lstyle++;
        }

        result->set(lchar, c);

        lchar++;
    }

    while (lchar < 128) {
        result->set(lchar, 0);
    }

    while (lstyle < 30) {
        result->setFont(lchar, 0);
        result->setColor(lchar, defaultColor);
    }

    return result;
}

CompiledLTL *CompiledLTL::compile_string(const char *raw_ltl) {
    Color dc = Color();
    dc.r = 200;
    dc.g = 200;
    dc.b = 200;

    return compile_string(raw_ltl, dc);
}
