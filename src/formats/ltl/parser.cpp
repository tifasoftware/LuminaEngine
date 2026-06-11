#include "ltl.h"

#include <iostream>

LTLParser::LTLParser() {
    strncpy(workingString, "",255);
    parsing = false;
    index = 0;
    size = 0;
    style_flag = 0;
    flag_backlog = nullptr;
}

LTLParser::~LTLParser() {
    if (flag_backlog != nullptr) delete flag_backlog;
}

void LTLParser::parseString(const char *ws) {
    strncpy(workingString, ws,255);
    parsing = true;
    index = 0;
    if (flag_backlog != nullptr) delete flag_backlog;
    flag_backlog = new std::list<uint8_t>();
}

bool LTLParser::advance() {
    if (workingString[index] == 0) return false;
    return true;
}

char LTLParser::nextChar() {
    //Parse Escaped < '%<'
    if (workingString[index] == '%' && workingString[index + 1] == '<') {
        index++;
    }

    while (workingString[index] == '<') {
        index++;
        if (workingString[index] == '/') {
            if (flag_backlog->empty()) {
                style_flag = 0;
                flag_backlog->pop_back();
            } else {
                style_flag = flag_backlog->back();
            }
        } else {
            flag_backlog->push_back(style_flag);

            bool acolor = (style_flag & 1) != 0;
            bool bold = (style_flag & 2) != 0;
            bool italic = (style_flag & 4) != 0;

            char ns = workingString[index];

            if (ns == 'b') bold = true;
            if (ns == 'i') italic = true;
            if (ns == 'c') {
                acolor = true;
                index++;
                if (workingString[index] == ':'
                    && workingString[index + 1] == '#'
                    && workingString[index + 8] == '>')
                {
                    index += 2;

                    int c[3];

                    for (int i = 0; i < 3; i++) {
                        char hexvalue[2];
                        hexvalue[0] = workingString[index];
                        hexvalue[1] = workingString[index + 1];

                        c[i] = std::stoi(hexvalue, 0, 16);
                        index += 2;
                    }

                    color.r = c[0];
                    color.g = c[1];
                    color.b = c[2];
                }
            }

            style_flag = 0;
            if (acolor) style_flag += 1;
            if (bold) style_flag += 2;
            if (italic) style_flag += 4;
        }

        while (workingString[index - 1] != '>') {
            //std::cout << workingString[index];
            index++;
        }
    }

    index++;
    return workingString[index - 1];
}

bool LTLParser::canPrint() {
    if (workingString[index] == '%' && workingString[index + 1] == '<') {
        return true;
    }

    if (workingString[index] == '<') {
        return false;
    }
    return true;
}