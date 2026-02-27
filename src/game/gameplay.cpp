#include <game/gameplay.h>

GamePlay::GamePlay()
{
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMECONTROLLER);

    // Enable png support for SDL2_image
    IMG_Init(IMG_INIT_PNG);

    window = SDL_CreateWindow(
        "window",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        480,
        272,
        0
    );

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
        SDL_Delay(REDRAW_DELAY);
    }

    SDL_Delay(3000);

    f->FadeOut(1.0f);

    while (f->isFading()){
        r->clear();
        r->drawSprite(0, 0, 0);
        f->Render(1.0f / FRAME_RATE);
        r->present();
        SDL_Delay(REDRAW_DELAY);
    }

    r->unloadAllTextures();

    r->clear();
    r->present();

    tm = new TileMap("maptest.lmap", r);

    lumina = new Character();

    SDL_Delay(1000);

    WorldStart();
}

void GamePlay::Exit()
{
    snd->shutdown();
    r->shutdown();
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void GamePlay::GameLoop()
{
    if (!inTransition)
    {
        switch (gameState)
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
        SDL_Delay(REDRAW_DELAY);
    }
}

bool GamePlay::gameRunning()
{
    if (gameState == EXIT) return false;
    return true;
}

void GamePlay::SwitchState(GameState newState)
{
    switch (gameState)
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

        case EXIT:
        break;
    }

    SDL_Delay(200);

    switch (newState)
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

        case EXIT:
        break;
    }

    gameState = newState;
}