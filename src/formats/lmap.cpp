#include <formats/lmap.h>
#include <iostream>
#include <stdio.h>
#include <platform/platform.h>
#include <platform/universalsdl.h>

#ifdef PLATFORM_3DS
#include "3ds.h"
#endif

#include "common/utils.h"

LMAPLoader::LMAPLoader(const char* file)
{
    this->file = file;
}

LMAPHeader* LMAPLoader::load()
{
    LMAPHeader* lmap = (LMAPHeader*)malloc(sizeof(LMAPHeader));
    if (!lmap) { return nullptr; }

    FILE* in = fopen(LuminaUtils::osPath(file).c_str(), "rb");
    if (!in) {
        free(lmap);
#ifdef PLATFORM_3DS
        svcBreak(USERBREAK_PANIC);
#endif
        SDL_Log("Error opening file %s", LuminaUtils::osPath(file).c_str());
        return nullptr;
    }
    fread(lmap, sizeof(LMAPHeader), 1, in);
    fclose(in);

    return lmap;
}