#include <formats/lmap.h>
#include <iostream>
#include <stdio.h>

LMAPLoader::LMAPLoader(const char* file)
{
    this->file = file;
}

LMAPHeader LMAPLoader::load()
{
    LMAPHeader lmap;
    FILE* in = fopen(file, "rb");
    fread(&lmap, sizeof(LMAPHeader), 1, in);
    fclose(in);

    return lmap;
}