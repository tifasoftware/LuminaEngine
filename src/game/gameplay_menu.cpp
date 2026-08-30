#include <platform/platform.h>
#include <platform/universalsdl.h>

#include "gameplay.h"
#include "common/types.h"
#include "graphics/renderer.h"
#include "vgui/button.h"
#include "vgui/panel.h"

#ifdef PLATFORM_PSP
#include <pspkerneltypes.h>
#include <pspsysmem.h>
#endif

#include <game/gameplay.h>

#include "common/utils.h"

void GamePlay::MenuStart()
{
    sec_act = new Menu(PAUSE_MENU, r, snd, &gps);
    sec_act->activate();
    controller->Possess(sec_act);

    f->FadeIn(0.5f);

    while (f->isFading())
    {
        r->clear();

        sec_act->render();
        // Draw everything on a white background
        
        if (f->isFading()){
            f->Render(1.0f / FRAME_RATE);
        }

        r->present();
        
        SDL_Delay(REDRAW_DELAY);
    }

    gps.inTransition = false;
}

void GamePlay::MenuDraw()
{
    if (gps.inTransition) return;
        controller->SendInput();

        // Clear the screen
        r->clear();

        //if (text != nullptr)
        sec_act->render();
        // Draw everything on a white background
        
        r->present();
        if (gps.wantNewState) SwitchState();
}

void GamePlay::MenuExit()
{
    sec_act->deactivate();
    controller->Release();
    gps.inTransition = true;

    f->FadeOut(0.5f);

    while (f->isFading())
    {
        r->clear();

        sec_act->render();
        // Draw everything on a white background
        
        if (f->isFading()){
            f->Render(1.0f / FRAME_RATE);
        }

        r->present();
        LuminaUtils::LuminaDelay(REDRAW_DELAY);
    }

    snd->unloadAllSFX();
    r->unloadAllTextures();

    delete sec_act;
    sec_act = nullptr;

}