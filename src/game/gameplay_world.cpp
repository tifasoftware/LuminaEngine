#include <game/gameplay.h>

#include "common/utils.h"
#include "entities/entity.h"

void GamePlay::WorldStart() {
    tm = new TileMap(mapName, &gps, lumina, r);
    fontAtlas = r->loadTexture("fontatlas.png");
    dialogue = new Dialogue(r);
    dialogue->SetFont(fontAtlas);

    tm->loadMap();
    tm->findSpawn(lastMapName);
    controller->Possess(tm);
    ChangeMusic(tm->getBGMFile());
    lumina->loadCharacterSprite(r);

    if (newMap) {
        SpawnDef sp = tm->getSpawn();

        gps.characterX = SCREEN_W / 2;
        gps.characterY = SCREEN_H / 2;
        gps.screenX = sp.location.x - (SCREEN_W / 2);
        gps.screenY = sp.location.y - (SCREEN_H / 2);
        newMap = false;
    }
    tm->preShift(gps.screenX, gps.screenY);
    f->FadeIn(0.5f);

    inTransition = false;
    if (!introShown) dialogue->DisplayDialogue("Welcome to Lumina Engine");
    controller->Possess(dialogue);
    controller->QueuePawn(tm);
    introShown = true;
}

void GamePlay::WorldDraw()
{
        controller->SendInput();

        tm->updateMap();

        // Clear the screen
        r->clear();

        tm->drawMap();

        if (f->isFading()){
            f->Render(1.0f / FRAME_RATE);
        }

        if (dialogue->isEngaged()) dialogue->draw();

        r->present();
        if (wantNewState) SwitchState();
}

void GamePlay::WorldExit()
{
    char countText[32];
    snprintf(countText, sizeof(countText), "%d", tm->getActiveEntities());
    //Text t = Text(countText, fontAtlas);
    //Text text = Text(mapName, fontAtlas, 16,16);
    inTransition = true;

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
        SDL_Delay(REDRAW_DELAY);
    }

    controller->Release();
    tm->disposeMap();
    delete tm;
    tm = nullptr;
    
    r->unloadAllTextures();

    //delete text;
    delete dialogue;
}

void GamePlay::RequestMapChange(const char *newMapName) {
    wantNewState = true;
    newMap = true;
    strncpy(lastMapName, mapName, sizeof(lastMapName) - 1);  // copy current into last
    strncpy(mapName, newMapName, sizeof(mapName) - 1);
}

void GamePlay::ChangeMusic(const char *newMusic) {
    if (strcmp(music, newMusic) != 0 && strcmp(music, "") != 0) {
        strncpy(music, newMusic, sizeof(music) - 1);
        snd->stopMusic();
        snd->startMusic(music);
    }
}



