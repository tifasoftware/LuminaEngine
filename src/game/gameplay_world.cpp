#include <game/gameplay.h>

#include "common/utils.h"
#include "entities/entity.h"

void GamePlay::WorldStart() {
    tm = new TileMap(gps.mapName, &gps, lumina, r);

    fontAtlas = r->loadTexture("fontatlas.png");
    dialogue = new Dialogue(r, tm);
    dialogue->SetFont(fontAtlas);


    tm->loadMap();
    tm->findSpawn(gps.lastMapName);
    tm->SetDebugFont(fontAtlas);
    controller->Possess(tm);
    ChangeMusic(tm->getBGMFile());
    lumina->loadCharacterSprite(r);

    scriptEngine = new ScriptEngine(dialogue, &gps, tm);

    if (gps.newMap) {
        SpawnDef sp = tm->getSpawn();

        gps.characterX = SCREEN_W / 2;
        gps.characterY = SCREEN_H / 2;
        gps.screenX = sp.location.x - (SCREEN_W / 2);
        gps.screenY = sp.location.y - (SCREEN_H / 2);
        gps.newMap = false;
    }
    tm->preShift(gps.screenX, gps.screenY);
    f->FadeIn(0.5f);

    gps.inTransition = false;
    if (!gps.introShown) {
        scriptEngine->runScript("gamestart.lua", "onCall");
        //dialogue->DisplayDialogue("Welcome to Lumina Engine");

    }
    gps.introShown = true;
    SDL_BP_SetClearColor(r->getRenderer(),255,0,255);

}

void GamePlay::WorldDraw()
{
        controller->SendInput();

        scriptEngine->updateScripts();
        tm->updateMap();

        // Clear the screen
        r->clear();

        tm->drawMap();

        if (f->isFading()){
            f->Render(1.0f / FRAME_RATE);
        }

        if (dialogue->isEngaged()) {
            dialogue->draw();
            if (!dialogue->getActive()) {
                controller->Possess(dialogue);
                controller->QueuePawn(tm);
            }
        }

        r->present();
        if (gps.wantNewState) SwitchState();
}

void GamePlay::WorldExit()
{
    char countText[32];
    snprintf(countText, sizeof(countText), "%d", tm->getActiveEntities());
    //Text t = Text(countText, fontAtlas);
    //Text text = Text(mapName, fontAtlas, 16,16);
    gps.inTransition = true;

    gps.screenX = tm->getOffsetX();
    gps.screenY = tm->getOffsetY();

    f->FadeOut(0.5f);

    while (f->isFading())
    {
        r->clear();

        // Draw the 'grass' sprite
        tm->drawMap();

        //t.Render(r);

        lumina->drawCharacter(gps.characterX, gps.characterY, 0, 0, r);

        if (f->isFading()){
            f->Render(1.0f / FRAME_RATE);
        }
        // Draw everything on a white background
        
        r->present();
        LuminaUtils::LuminaDelay(REDRAW_DELAY);
    }

    controller->Release();
    tm->disposeMap();
    delete scriptEngine;
    delete tm;
    tm = nullptr;
    
    r->unloadAllTextures();

    //delete text;
    delete dialogue;
}

void GamePlay::ChangeMusic(const char *newMusic) {
    if (strcmp(gps.music, newMusic) != 0 && strcmp(gps.music, "") != 0) {
        strncpy(gps.music, newMusic, sizeof(gps.music) - 1);
        snd->stopMusic();
        snd->startMusic(gps.music);
    }
}



