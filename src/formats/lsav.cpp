#include <formats/lsav.h>
#include <iostream>
#include <stdio.h>
#include <platform/platform.h>
#include <platform/universalsdl.h>

#ifdef PLATFORM_3DS
#include "3ds.h"
#endif

#include "common/utils.h"

LSAVLoader::LSAVLoader(const char* file)
{
    this->file = file;
}

LSAVHeader* LSAVLoader::load()
{
    LSAVHeader* lsav = (LSAVHeader*)malloc(sizeof(LSAVHeader));
    if (!lsav) { return nullptr; }

    FILE* in = fopen(LuminaUtils::osPath(file).c_str(), "rb");
    if (!in) {
        free(lsav);
#ifdef PLATFORM_3DS
        svcBreak(USERBREAK_PANIC);
#endif
        SDL_Log("Error opening file %s", LuminaUtils::osPath(file).c_str());
        return nullptr;
    }
    fread(lsav, sizeof(LSAVHeader), 1, in);
    fclose(in);

    return lsav;
}

LSAVWriter::LSAVWriter(const char* file) {
    this->file = file;
}

int LSAVWriter::write(LSAVHeader* lsav) {
    if (!lsav) { return -1; }

    FILE* out = fopen(LuminaUtils::osPath(file).c_str(), "wb");
    if (!out) {
        return -1;
    }

    fwrite(lsav, sizeof(LSAVHeader), 1, out);
    fclose(out);

    return 0;
}
