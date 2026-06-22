#include <platform/platform.h>
#include <platform/universalsdl.h>
#include <string>
#include <cstdio>

#ifdef PLATFORM_PSP
#include <pspkernel.h>
#include <pspdisplay.h>
#endif
#include "lumina.h"

#ifdef PLATFORM_OSX
#include <unistd.h>
#include <limits.h>
#endif

#ifdef PLATFORM_3DS
#include <3ds.h>
#endif

#ifdef PLATFORM_DREAMCAST
#include <kos.h>
KOS_INIT_FLAGS(INIT_DEFAULT);
#endif



int main(int argc, char *argv[])
{
#ifdef PLATFORM_DREAMCAST
    printf("Hello Lumina\n");
#endif

#ifdef PLATFORM_PSP
    //freopen("ms0:/log.txt", "w", stdout);
    //setvbuf(stdout, NULL, _IONBF, 0); // unbuffered
    //freopen("ms0:/err.txt", "w", stderr);
#endif
    auto gp = new GamePlay();

#ifdef PLATFORM_3DS
    aptSetSleepAllowed(true);

    aptHookCookie hookCookie;
    aptHook(&hookCookie, [](APT_HookType hook, void*) {
        switch (hook) {
            case APTHOOK_ONSLEEP:
                Mix_PauseMusic();
                Mix_Pause(-1);
                break;
            case APTHOOK_ONWAKEUP:
                Mix_ResumeMusic();
                Mix_Resume(-1);
                break;
            default:
                break;
        }
    }, nullptr);

    while (gp->gameRunning() && aptMainLoop()) {
        if (aptShouldClose()) {
            gp->Exit();
            return 0;
            break;
        }

        if (!aptIsActive()) {
            // suspended by HOME menu, just wait
            gspWaitForVBlank();
            continue;
        }

        gp->GameLoop();
    }
#else
    while (gp->gameRunning()) {
        gp->GameLoop();
    }
#endif
    gp->Exit();

    return 0;
}


