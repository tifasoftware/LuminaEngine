#include "ltl.h"

CompiledLTL::CompiledLTL() {
    /*lucii_string = new uint8_t[128];
    font_table = new uint8_t[30];
    color_table = new Color[30];*/

    print_length = 0;
}

CompiledLTL::~CompiledLTL() {
    /*delete lucii_string;
    delete font_table;
    delete color_table;*/
}

Color CompiledLTL::getColor(int index) {
    int style = lucii_string[index] - 2;
    return color_table[style];
}

int CompiledLTL::getFont(int index) {
    int style = lucii_string[index] - 2;
    return font_table[style];
}

void CompiledLTL::compile_string(CompiledLTL *result, const char *raw_ltl) {
    Color dc = Color();
    dc.r = 200;
    dc.g = 200;
    dc.b = 200;

    compile_string(result, raw_ltl, dc);
}

void CompiledLTL::compile_string(CompiledLTL *result, const char *raw_ltl, Color defaultColor) {
    result->print_length = 0;

    int font = 0;
    Color color = Color();
    bool applyColor = false;
    LTLParser parser;

    int lchar = 1;
    int lstyle = 0;

    result->setColor(lstyle, defaultColor);
    result->setFont(lstyle,font);
    result->set(0, lstyle + 2);
    lstyle++;

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
        }

        if (applyNewStyle) {
            result->setFont(lstyle, font);

            result->set(lchar, lstyle + 2);

            lchar++;
            lstyle++;
        }

        result->set(lchar, c);
        result->print_length++;
        lchar++;
    }

    while (lchar < 128) {
        result->set(lchar, 0);
        lchar++;
    }

    while (lstyle < 28) {
        result->setFont(lstyle, 0);
        result->setColor(lstyle, defaultColor);
        lstyle++;
    }

}
