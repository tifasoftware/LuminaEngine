#pragma once

#ifdef __PSP__
    #define PLATFORM_PSP
    #define SCREEN_W 480
    #define SCREEN_H 272
    #define SCREEN_SCALE 1
    #define LIB_SDL2
#else
    #define PLATFORM_PC
    #define SCREEN_W 480
    #define SCREEN_H 272
    #ifdef LIB_SDL1
        #define SCREEN_SCALE 1
    #else
        #define SCREEN_SCALE 2
    #endif
#endif
#ifdef __APPLE__
    #define PLATFORM_OSX
#endif
#ifdef __WIN32__
    #define PLATFORM_WINDOWS
#endif
#ifdef __3DS__
    #define PLATFORM_3DS
    #define SCREEN_W 400
    #define SCREEN_H 240
    #define SCREEN_SCALE 1
    #define LIB_SDL1
#endif