#include "utils.h"


Orientation LuminaUtils::FlipOrientation(Orientation orientation) {
    if (orientation == FACE_UP) return FACE_DOWN;
    if (orientation == FACE_RIGHT) return FACE_LEFT;
    if (orientation == FACE_DOWN) return FACE_UP;
    if (orientation == FACE_LEFT) return FACE_RIGHT;
    return orientation;
}
