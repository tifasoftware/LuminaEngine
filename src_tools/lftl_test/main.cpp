#include <iostream>
#include <vgui/lftl.h>

int main(int argc, char *argv[]) {
    for (std::string line; std::getline(std::cin, line);) {
        LFTLParser parser;

        const char* cstr = line.c_str();

        parser.parseString(cstr);

        while (parser.advance()) {
            if (parser.canPrint()) std::cout << parser.nextChar();
        }

        std::cout << std::endl;
    }
    return 0;
}