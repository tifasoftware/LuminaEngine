#pragma once
#include "types.h"

class LuminaUtils {
    public:
    static Orientation FlipOrientation(Orientation orientation);
    static bool IsFacingEachOther(Orientation player, Orientation other);
};
