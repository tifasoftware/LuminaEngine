#include "mdisplay.h"

int MobileDisplay::GetScreenHeight() {
    return 600;
}

int MobileDisplay::GetScreenWidth() {
    return 800;
}

int MobileDisplay::GetDrawHeight() {
    return GetScreenHeight();
}

int MobileDisplay::GetDrawWidth() {
    return GetScreenWidth();
}

int MobileDisplay::GetRecommendedScale()
{
    return 1;
}