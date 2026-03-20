#include <game/gameplay.h>

#include "common/utils.h"
#include "entities/entity.h"

void GamePlay::WorldStart() {
    tm = new TileMap(mapName, r);
    fontAtlas = r->loadTexture("fontatlas.png");
    //text = new Text("The Quick Brown Fox Jumps Over The Lazy Dog", fontAtlas, 16, 16);

    tm->loadMap();
    tm->findSpawn(lastMapName);
    ChangeMusic(tm->getBGMFile());
    lumina->loadCharacterSprite(r);

    if (newMap) {
        SpawnDef sp = tm->getSpawn();

        luminaX = SCREEN_W / 2;
        luminaY = SCREEN_H / 2;
        offsetX = sp.location.x - (SCREEN_W / 2);
        offsetY = sp.location.y - (SCREEN_H / 2);
        newMap = false;
    }
    tm->preShift(offsetX, offsetY);
    f->FadeIn(0.5f);
    inTransition = false;
}

void GamePlay::WorldDraw()
{
    if (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    // End the loop if the programs is being closed
                    RequestSwitchState(EXIT);
                    break;
                case SDL_CONTROLLERDEVICEADDED:
                    // Connect a controller when it is connected
                    SDL_GameControllerOpen(event.cdevice.which);
                    break;
                case SDL_CONTROLLERBUTTONDOWN:
                    if(event.cbutton.button == SDL_CONTROLLER_BUTTON_START) {
                        // Open Main Menu if start is pressed
                        RequestSwitchState(MENU);
                    } 
                    else if (event.cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_UP) {
                        luminaMoveY = -1 * luminaMoveRate;
                    }
                    else if (event.cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_DOWN) {
                        luminaMoveY = luminaMoveRate;
                    }
                    else if (event.cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_LEFT) {
                        luminaMoveX = -1 * luminaMoveRate;
                    }
                    else if (event.cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_RIGHT) {
                        luminaMoveX = luminaMoveRate;
                    }
                    break;
                case SDL_CONTROLLERBUTTONUP:
                    if (event.cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_UP) {
                        luminaMoveY = 0;
                    }
                    else if (event.cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_DOWN) {
                        luminaMoveY = 0;
                    }
                    else if (event.cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_LEFT) {
                        luminaMoveX = 0;
                    }
                    else if (event.cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_RIGHT) {
                        luminaMoveX = 0;
                    }
                    break;
            }
        }

        tm->updateEntities();

        if (!tm->isColliding(luminaX + luminaMoveX, luminaY + luminaMoveY)){
            if (!tm->scrollX(luminaMoveX, luminaX + luminaMoveX)) luminaX += luminaMoveX;
            if (!tm->scrollY(luminaMoveY, luminaY + luminaMoveY)) luminaY += luminaMoveY;
        }

        //bool error = false;

        if (luminaMoveX != 0 || luminaMoveY != 0) {
            Entity* colTrig = tm->getCollidingTrigger(luminaX, luminaY);
            if (colTrig != nullptr) {
                if (colTrig->getType() == TRIGGER_WARP) {
                    if (colTrig->hasProperty("map")) RequestMapChange(colTrig->getProperty("map"));
                }
            }
        }

        // Clear the screen
        r->clear();

        // Draw the 'grass' sprite
        tm->drawMap();
        //text->Render(r);

        //if (error) r->drawTile(0,0,0,0);

        lumina->animate(FRAME_RATE, luminaMoveX, luminaMoveY);
        lumina->drawCharacter(luminaX, luminaY, luminaMoveX, luminaMoveY, r);

        if (f->isFading()){
            f->Render(1.0f / FRAME_RATE);
        }
        // Draw everything on a white background
        
        r->present();
        if (wantNewState) SwitchState();
}

void GamePlay::WorldExit()
{
    Text text = Text(mapName, fontAtlas, 16,16);
    inTransition = true;

    offsetX = tm->getOffsetX();
    offsetY = tm->getOffsetY();

    f->FadeOut(0.5f);

    while (f->isFading())
    {
        r->clear();

        // Draw the 'grass' sprite
        tm->drawMap();

        text.Render(r);

        lumina->drawCharacter(luminaX, luminaY, 0, 0, r);

        if (f->isFading()){
            f->Render(1.0f / FRAME_RATE);
        }
        // Draw everything on a white background
        
        r->present();
        SDL_Delay(REDRAW_DELAY);
    }

    tm->disposeMap();
    delete tm;
    
    r->unloadAllTextures();

    //delete text;
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



