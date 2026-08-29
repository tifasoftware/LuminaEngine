#include <game/gameplay.h>

#include "common/utils.h"
#include "entities/entity.h"

void GamePlay::WorldStart() {
    tm = new TileMap(gps.mapName, &gps, lumina, r);

    tm->loadMap();
    tm->findSpawn(gps.lastMapName);
    tm->activate();
    controller->Possess(tm);
    ChangeMusic(tm->getBGMFile());
    lumina->loadCharacterSprite(r);

    scriptEngine = new ScriptEngine(&gps, tm);
    gps.unpauseScript = false;

    if (gps.newMap) {
        SpawnDef sp = tm->getSpawn();

        gps.characterX = r->GetWidth() / 2;
        gps.characterY = r->GetHeight() / 2;
        gps.screenX = sp.location.x - (r->GetWidth() / 2);
        gps.screenY = sp.location.y - (r->GetHeight() / 2);
        gps.newMap = false;
    }
    tm->preShift(gps.screenX, gps.screenY);
    f->FadeIn(0.5f);

    gps.inTransition = false;
    if (!gps.introShown) {
        scriptEngine->runScript("gamestart.lua", "onCall");
    }
    gps.introShown = true;
    SDL_BP_SetClearColor(r->getRenderer(),255,0,255);

}

void GamePlay::WorldDraw()
{
        controller->SendInput();

        scriptEngine->updateScripts(gps.unpauseScript);
        gps.unpauseScript = false;

        tm->updateMap();

        // Clear the screen
        r->clear();

        tm->drawMap();

        if (f->isFading()){
            f->Render(1.0f / FRAME_RATE);
        }


        Overlay* overlay = gps.GetOverlay();
        if (overlay != nullptr) {
            if (overlay->isEngaged()) {
                overlay->draw();
                if (!overlay->getActive()) {
                    controller->Possess(overlay);
                    controller->QueuePawn(tm);
                }
            } else gps.unpauseScript = true;
        }

#if (defined(PLATFORM_PC) && defined(USER_LIGHTNING)) || defined(PLATFORM_ANDROID)
        osc->draw();
#endif

        r->present();
        if (gps.wantCallScript) {
            scriptEngine->runScript(gps.nextScript, "onCall");
            gps.wantCallScript = false;
        }
        if (gps.wantNewState) SwitchState();
}

void GamePlay::WorldExit()
{
    gps.inTransition = true;

    gps.screenX = tm->getOffsetX();
    gps.screenY = tm->getOffsetY();

    f->FadeOut(0.5f);

    while (f->isFading())
    {
        r->clear();

        tm->drawMap();

        if (f->isFading()){
            f->Render(1.0f / FRAME_RATE);
        }
        // Draw everything on a white background
        
        r->present();
        LuminaUtils::LuminaDelay(REDRAW_DELAY);
    }

    tm->deactivate();
    controller->Release();
    tm->disposeMap();
    delete scriptEngine;
    delete tm;
    tm = nullptr;
    
    r->unloadAllTextures();
}



