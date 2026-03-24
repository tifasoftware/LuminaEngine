#pragma once
#include <string>

#include "types.h"

class LuminaUtils {
    public:
    static Orientation FlipOrientation(Orientation orientation);
    static bool IsFacingEachOther(Orientation player, Orientation other);
    const char* appendExtension(const char* filename, const char* extension);
    static void LuminaDelay(int ms);
    static std::string osPath(const char* relpath);
};
