#include "utils.h"

#include <string>
#include <unistd.h>
#include <platform/platform.h>
#include <platform/universalsdl.h>


#ifdef PLATFORM_OSX
#include <mach-o/dyld.h>
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
#ifdef PLATFORM_PSP
    SDL_Delay(ms);
#endif
#ifdef PLATFORM_PC
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
}

std::string LuminaUtils::osPath(const char *relpath) {
    std::string file = std::string(relpath);
    std::string base = "";
    std::string path;

#ifdef PLATFORM_OSX
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

#ifdef PLATFORM_3DS
    base = "romfs:/";
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
