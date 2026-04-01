#pragma once

#include <string>

static char* SDL_GetBasePath() {
    std::string basepath = "./";
    char* ret = new char[256];
    strncpy(ret, basepath.c_str(), 255);
    return ret;
}

static void SDL_Log(char * format, ...) {
    //no ops
}