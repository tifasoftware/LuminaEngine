#include <cstdint>
#include <cstring>
#include <string>
#include <list>

struct Color {
    uint8_t r = 0;
    uint8_t g = 0;
    uint8_t b = 0;

    Color() {
        r = 0;
        g = 0;
        b = 0;
    }

    Color(uint8_t r, uint8_t g, uint8_t b) {
        this->r = r;
        this->g = g;
        this->b = b;
    }

    bool operator==(const Color& c) const {
        if (c.r == r && c.g == g && c.b == b) return true;
        return false;
    }

    bool operator!=(const Color& c) const {
        if (c.r != r || c.g != g || c.b != b) return true;
        return false;
    }
};

class LTLParser {
public:
    LTLParser();
    ~LTLParser();
    void parseString(std::string ws);
    void parseString(const char* ws);
    bool advance();
    bool canPrint();
    char nextChar();
    int nextFont() { return (style_flag - (style_flag % 2)) / 2; }
    bool nextApplyColor() { return style_flag % 2 != 0; }
    Color nextColor() { return color; }

private:
    char workingString[256];
    bool parsing;
    uint8_t style_flag;
    std::list<uint8_t>* flag_backlog;
    Color color;
    int index;
    int size;
};

class LTLCompiler {
    public:
    LTLCompiler();

    private:

};

class CompiledLTL {
    public:
    CompiledLTL(int length, int styles, int colors);
    ~CompiledLTL();

    bool isChar(int index);
    char getChar(int index);
    int getFont(int index);
    Color getColor(int index);

    void set(int index, int value) { lucii_string[index] = value; }
    void setFont(int index, int value) { font_table[index] = value; }
    void setColor(int index, Color value) { color_table[index] = value; }

    private:
    uint8_t* lucii_string;
    uint8_t* font_table;
    Color* color_table;
};