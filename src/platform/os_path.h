#pragma once
#include "platform.h"
#include <SDL2/SDL.h>
#include <string>

inline const char* osPath(const char* relpath) {
    return relpath;
}