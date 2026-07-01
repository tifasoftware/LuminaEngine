#include "utils.h"

#include <string>
#include <unistd.h>
#include <platform/platform.h>
#include <platform/universalsdl.h>


#ifdef PLATFORM_OSX
#include <mach-o/dyld.h>
#endif

#ifdef PLATFORM_3DS
#include <3ds.h>
#endif

#include "graphics/Renderer.h"

Orientation LuminaUtils::FlipOrientation(Orientation orientation) {
    if (orientation == FACE_UP) return FACE_DOWN;
    if (orientation == FACE_RIGHT) return FACE_LEFT;
    if (orientation == FACE_DOWN) return FACE_UP;
    if (orientation == FACE_LEFT) return FACE_RIGHT;
    return orientation;
}

bool LuminaUtils::IsFacingEachOther(Orientation player, Orientation other) {
    if (player == FlipOrientation(other)) return true;
    if (other == FACE_ALL) return true;
    if (other == FACE_UD && (player == FACE_UP || player == FACE_DOWN)) return true;
    if (other == FACE_LR && (player == FACE_RIGHT || player == FACE_LEFT)) return true;
    return false;
}

const char* LuminaUtils::appendExtension(const char *filename, const char *extension) {
    char buffer[256];

    snprintf(buffer, 256, "%s.%s", filename, extension);

    const char* result = buffer;

    return result;
}

void LuminaUtils::LuminaDelay(int ms) {
#if defined(PLATFORM_PSP) || defined(PLATFORM_DREAMCAST) || defined(PLATFORM_GAMECUBE) || defined(PLATFORM_PS2) || defined(PLATFORM_XBOX)
    SDL_Delay(ms);
#endif

#if defined(PLATFORM_PC) || defined(PLATFORM_ANDROID)
    int delay = 1000 / FRAME_RATE;
    int cycles = ms / delay;
    for (int i = 0; i < cycles; i++) {
        SDL_Event event;
        if (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) exit(0);
        }
        SDL_Delay(delay);
    }
#endif
#ifdef PLATFORM_3DS
    int delay = ms / 16.6667f;
    for (int i = 0; i < delay; i++) {
        if (aptShouldClose())
            break;
        gspWaitForVBlank();
    }
#endif
}

std::string LuminaUtils::osPath(const char *relpath) {
    std::string file = std::string(relpath);
    std::string base = "";
    std::string path;

#if defined(PLATFORM_OSX)
    char execPath[PATH_MAX];
    uint32_t size = sizeof(execPath);

    if (_NSGetExecutablePath(execPath, &size) == 0) {
        std::string macpath(execPath);
        size_t pos = macpath.rfind("Contents/MacOS");
        if (pos != std::string::npos) {
            path = macpath.substr(0, pos) + "Contents/Resources/" + file;
            FILE* logFile = fopen("/tmp/lumina.log", "a");
            fprintf(logFile, "execPath: %s\n", execPath);
            fprintf(logFile, "final path: %s\n", path.c_str());
            fclose(logFile);
        }
    }
    return path;
#else
#if defined(PLATFORM_3DS)
    base = "romfs:/";
#elif defined(PLATFORM_PS2)
    base = "cdrom0:";
    // base = "host:";
#elif defined(PLATFORM_DREAMCAST)
    //base = "/cd/";
     base = "/rd/";
#elif defined(PLATFORM_ANDROID)
     //base = std::string(SDL_AndroidGetInternalStoragePath()) + "/";
    base = "";
#else
    if (base.empty()) {
        char* sdl_base = SDL_GetBasePath();
        base = std::string(sdl_base);
    }
#endif
    path = (base + file);

    return path;
#endif
}
