#include <cstdint>

struct Color {
    uint8_t r = 0;
    uint8_t g = 0;
    uint8_t b = 0;
};

class LFTLParser {
public:
    LFTLParser();
    ~LFTLParser() {}
    void parseString(char* ws);
    void advance();
    char nextChar() { return workingString[index]; }
    int nextFont() { return (style_flag - (style_flag % 2)) / 2; }
    bool nextApplyColor() { return style_flag % 2 == 0; }
    Color nextColor() { return color; }

private:
    char* workingString;
    bool parsing;
    uint8_t style_flag;
    Color color;
    int index;
};