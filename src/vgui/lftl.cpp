#include "lftl.h"

LFTLParser::LFTLParser() {
    workingString = nullptr;
    parsing = false;
    index = 0;
    style_flag = 0;
}

void LFTLParser::parseString(char *ws) {
    workingString = ws;
    parsing = true;
    index = 0;
}

void LFTLParser::advance() {
    if (workingString == nullptr) return;
    index++;

    //Parse Escaped < '%<'
    if (workingString[index] == '%' && workingString[index + 1] == '<') {
        index++;
    }
}
