#pragma once

#ifdef __PSP__
    #define PLATFORM_PSP
    #define SCREEN_W 480
    #define SCREEN_H 272
    #define SCREEN_SCALE 1
#else
    #define PLATFORM_PC
    #define SCREEN_W 480
    #define SCREEN_H 272
    #define SCREEN_SCALE 2
#endif