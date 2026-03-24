#include <formats/lmap.h>
#include <iostream>
#include <stdio.h>
#include <SDL2/SDL_log.h>

#include "common/utils.h"

LMAPLoader::LMAPLoader(const char* file)
{
    this->file = file;
}

LMAPHeader LMAPLoader::load()
{
    LMAPHeader lmap = {};
    FILE* in = fopen(LuminaUtils::osPath(file).c_str(), "rb");
    if (!in) {
        SDL_Log("Error opening file %s", LuminaUtils::osPath(file).c_str());
        return lmap;
    }
    fread(&lmap, sizeof(LMAPHeader), 1, in);
    fclose(in);

    return lmap;
}