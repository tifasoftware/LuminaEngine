#include <formats/lmap.h>
#include <iostream>
#include <stdio.h>
#include <platform/platform.h>
#include <platform/universalsdl.h>

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
        strncpy(lmap.magic, "FAIL", 4);
        SDL_Log("Error opening file %s", LuminaUtils::osPath(file).c_str());
        return lmap;
    }
    fread(&lmap, sizeof(LMAPHeader), 1, in);
    fclose(in);

    return lmap;
}