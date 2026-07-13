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

#if defined(PLATFORM_ANDROID)
    SDL_RWops* in = SDL_RWFromFile(LuminaUtils::osPath(file).c_str(),"r+b");
#else
    FILE* in = fopen(LuminaUtils::osPath(file).c_str(), "rb");
#endif
    if (!in) {
        free(lmap);
#ifdef PLATFORM_3DS
        svcBreak(USERBREAK_PANIC);
#endif
        SDL_Log("Error opening file %s", LuminaUtils::osPath(file).c_str());
        return nullptr;
    }

#if defined(PLATFORM_ANDROID)
    SDL_RWread(in, lmap, sizeof(LMAPHeader), 1);
    SDL_RWclose(in);
#else
    fread(lmap, sizeof(LMAPHeader), 1, in);
    fclose(in);
#endif

#if defined(__BYTE_ORDER) && __BYTE_ORDER == __BIG_ENDIAN || \
defined(__BIG_ENDIAN__) || \
defined(__ARMEB__) || \
defined(__THUMBEB__) || \
defined(__AARCH64EB__) || \
defined(_MIBSEB) || defined(__MIBSEB) || defined(__MIBSEB__)
    printf("This is a  BE arch");
    convertEndianess(lmap);
#endif

    return lmap;
}

void LMAPLoader::convertEndianess(LMAPHeader* lmap) {
    lmap->version = __builtin_bswap16(lmap->version);
    lmap->width = __builtin_bswap16(lmap->width);
    lmap->height = __builtin_bswap16(lmap->height);

    for (int i = 0; i < (64 * 64); i++) {
        lmap->tiles[i] = __builtin_bswap16(lmap->tiles[i]);
    }

    for (int i = 0; i < 64; i++) {
        lmap->entities[i].width = __builtin_bswap16(lmap->entities[i].width);
        lmap->entities[i].height = __builtin_bswap16(lmap->entities[i].height);
        lmap->entities[i].x = __builtin_bswap16(lmap->entities[i].x);
        lmap->entities[i].y = __builtin_bswap16(lmap->entities[i].y);
    }

    for (int i = 0; i < 16; i++) {
        lmap->spawnpoints[i].location.x = __builtin_bswap16(lmap->spawnpoints[i].location.x);
        lmap->spawnpoints[i].location.y = __builtin_bswap16(lmap->spawnpoints[i].location.y);
    }
}
