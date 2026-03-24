#include <formats/lmap.h>
#include <iostream>
#include <stdio.h>

#include "platform/os_path.h"

LMAPLoader::LMAPLoader(const char* file)
{
    this->file = file;
}

LMAPHeader LMAPLoader::load()
{
    LMAPHeader lmap = {};
    FILE* in = fopen(osPath(file), "rb");
    fread(&lmap, sizeof(LMAPHeader), 1, in);
    fclose(in);

    return lmap;
}