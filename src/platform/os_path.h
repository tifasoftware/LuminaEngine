#pragma once
#include "platform.h"
#include <SDL2/SDL.h>
#include <string>

inline const char* osPath(const char* relpath) {
#ifdef PLATFORM_OSX
    static std::string base = "";

    if (base.empty()) {
        char* sdlBase = SDL_GetBasePath();
        if (sdlBase) {
            base = std::string(sdlBase);
            delete sdlBase;
        } else {
            base = "./";
        }
    }

    return (base + relpath).c_str();
#else
    return relpath;
#endif
}