#include <game/gameplay.h>
#include <platform/platform.h>
#include <common/utils.h>

#ifdef PLATFORM_3DS
#include "3ds.h"
#endif

GamePlay::GamePlay()
{
#ifdef PLATFORM_3DS
    romfsInit();
#endif
#ifdef LIB_SDL1
    SDL_Init(SDL_INIT_EVERYTHING);
#else
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMECONTROLLER);
#endif

    // Enable png support for SDL2_image
    IMG_Init(IMG_INIT_PNG);

#ifdef PLATFORM_PSP
    window = SDL_CreateWindow(
        "window",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        480,
        272,
        0
    );
#endif
#ifdef PLATFORM_PC
    window = SDL_CreateWindow(
        "Lumina Engine",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        SCREEN_W * SCREEN_SCALE,
        SCREEN_H * SCREEN_SCALE,
        0
        );
    SDL_SetWindowFullscreen(window, 0);
    SDL_RaiseWindow(window);
    SDL_SetWindowInputFocus(window);
#endif
#ifdef PLATFORM_3DS
    window = SDL_CreateWindow(
        "window",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        SCREEN_W,
        SCREEN_H,
        0
    );
    SDL_ShowCursor(SDL_DISABLE);
#endif

    snd = new SoundSystem();
    r = new Renderer(window);

    snd->startMusic("bgm0.ogg");

    r->loadTexture("splash.png");

    f = new Fade(r);
    f->FadeIn(1.0f);

    while (f->isFading()){
        r->clear();
        r->drawSprite(0, 0, 0);
        f->Render(1.0f / FRAME_RATE);
        r->present();
        LuminaUtils::LuminaDelay(REDRAW_DELAY);
    }

    for (int i = 0; i < 180; i++) {
        r->clear();
        r->drawSprite(0, 0, 0);
        //f->Render(1.0f / FRAME_RATE);
        r->present();
        LuminaUtils::LuminaDelay(REDRAW_DELAY);
    }
    //LuminaUtils::LuminaDelay(3000);

    f->FadeOut(1.0f);

    while (f->isFading()){
        r->clear();
        r->drawSprite(0, 0, 0);
        f->Render(1.0f / FRAME_RATE);
        r->present();
        LuminaUtils::LuminaDelay(REDRAW_DELAY);
    }



    r->unloadAllTextures();

    r->clear();
    r->present();

    lumina = new Character();
    gps = GamePlayState();
    controller = new Controller();

    SDL_BP_SetClearColor(r->getRenderer(),0,150,255);

    for (int i = 0; i < 60; i++) {
        r->clear();
        //f->Render(1.0f / FRAME_RATE);
        r->present();
        LuminaUtils::LuminaDelay(REDRAW_DELAY);
    }

    strncpy(gps.lastMapName, "start", sizeof(gps.lastMapName) - 1);
    gps.newMap = true;
    WorldStart();
}

void GamePlay::Exit()
{
    snd->shutdown();
    r->shutdown();
    SDL_DestroyWindow(window);
    SDL_Quit();

#ifdef PLATFORM_3DS
    romfsExit();
#endif
}

void GamePlay::GameLoop()
{
    if (!gps.inTransition)
    {
        switch (gps.gameState)
            {
                case WORLD:
                WorldDraw();
                break;

                case BATTLE:
                break;

                case MENU:
                MenuDraw();
                break;

                case EXIT:
                break;
            }      
    }
    LuminaUtils::LuminaDelay(REDRAW_DELAY);
}

bool GamePlay::gameRunning()
{
    if (gps.gameState == EXIT) return false;
    return true;
}

void GamePlay::SwitchState()
{
    GameState oldState = gps.gameState;
    gps.gameState = TRANSITION;
    switch (oldState)
    {
        case WORLD:
        WorldExit();
        break;

        case MENU:
        MenuExit();
        break;

        case BATTLE:
        //BattleExit();
        break;

        default:
        break;
    }

    r->clear();
    r->present();
    LuminaUtils::LuminaDelay(200);

    switch (gps.newGameState)
    {
        case WORLD:
        WorldStart();
        break;

        case MENU:
        MenuStart();
        break;

        case BATTLE:
        //BattleStart();
        break;

        default:
        break;
    }

    gps.gameState = gps.newGameState;
    gps.wantNewState = false;
}