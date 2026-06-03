#include <iostream>
#include <vgui/lftl.h>

int main(int argc, char *argv[]) {
    for (std::string line; std::getline(std::cin, line);) {
        int font = 0;
        Color color = Color();
        bool applyColor = false;
        LFTLParser parser;

        const char* cstr = line.c_str();

        parser.parseString(cstr);

        while (parser.advance()) {
            char c = parser.nextChar();

            if (color != parser.nextColor()) {
                color = parser.nextColor();
            }

            if (applyColor != parser.nextApplyColor()) {
                applyColor = parser.nextApplyColor();

                if (applyColor) {
                    std::cout << "[";
                    std::cout << std::to_string(color.r);
                    std::cout << ",";
                    std::cout << std::to_string(color.g);
                    std::cout << ",";
                    std::cout << std::to_string(color.b);
                    std::cout << "]";
                } else {
                    std::cout << "[NORMAL]";
                }
            }

            if (font != parser.nextFont()) {
                font = parser.nextFont();

                switch (font) {
                    case 1:
                        std::cout << "*";
                        break;
                    case 2:
                        std::cout << "**";
                        break;
                    case 3:
                        std::cout << "***";
                        break;
                    case 0:
                    default:
                        std::cout << "*n*";
                        break;
                }
            }

            std::cout << c;
        }

        std::cout << std::endl;
    }
    return 0;
}