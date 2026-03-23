#include "utils.h"

#include <string>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_timer.h>
#include <platform/platform.h>

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