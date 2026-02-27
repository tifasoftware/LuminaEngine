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
    clink = snd->loadSFX("hover.wav");
    chime = snd->loadSFX("select.wav");

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

    SDL_Delay(1000);

    WorldStart();
}

void GamePlay::WorldStart()
{
    tm = new TileMap("maptest.lmap", r);

    lumina = new Character();

    text = new Text("The Quick Brown Fox Jumps Over The Lazy Dog", r->loadTexture("fontatlas.png"), 16, 16);

    lumina->loadCharacterSprite(r);
    luminaX = 480 / 2;
    luminaY = 272 / 2;

    f->FadeIn(1.0f);
}

void GamePlay::WorldDraw()
{
    if (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    // End the loop if the programs is being closed
                    gameState = EXIT;
                    break;
                case SDL_CONTROLLERDEVICEADDED:
                    // Connect a controller when it is connected
                    SDL_GameControllerOpen(event.cdevice.which);
                    break;
                case SDL_CONTROLLERBUTTONDOWN:
                    if(event.cbutton.button == SDL_CONTROLLER_BUTTON_START) {
                        // Close the program if start is pressed
                        SwitchState(EXIT);
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

        if (!tm->isColliding(luminaX + luminaMoveX, luminaY + luminaMoveY)){
            luminaX += luminaMoveX;
            luminaY += luminaMoveY;
        }
        // Clear the screen
        r->clear();

        // Draw the 'grass' sprite
        tm->drawMap();

        text->Render(r);

        lumina->drawCharacter(luminaX, luminaY, r);

        if (f->isFading()){
            f->Render(1.0f / FRAME_RATE);
        }
        // Draw everything on a white background
        
        r->present();
}

void GamePlay::WorldExit()
{
    f->FadeOut(2.0f);

    while (f->isFading())
    {
        r->clear();

        // Draw the 'grass' sprite
        tm->drawMap();

        text->Render(r);

        lumina->drawCharacter(luminaX, luminaY, r);

        if (f->isFading()){
            f->Render(1.0f / FRAME_RATE);
        }
        // Draw everything on a white background
        
        r->present();
        SDL_Delay(REDRAW_DELAY);
    }
}

void GamePlay::MenuDraw()
{
    if (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    // End the loop if the programs is being closed
                    gameState = EXIT;
                    break;
                case SDL_CONTROLLERDEVICEADDED:
                    // Connect a controller when it is connected
                    SDL_GameControllerOpen(event.cdevice.which);
                    break;
                case SDL_CONTROLLERBUTTONDOWN:
                    if(event.cbutton.button == SDL_CONTROLLER_BUTTON_START) {
                        // Close the program if start is pressed
                        snd->playSFX(chime);
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

        // Clear the screen
        r->clear();

        text->Render(r);
        // Draw everything on a white background
        
        r->present();
        
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
    switch (gameState)
        {
            case WORLD:
            WorldDraw();
            break;

            case BATTLE:
            break;

            case MENU:
            break;

            case EXIT:
            break;
        }
        SDL_Delay(REDRAW_DELAY);
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
        //MenuExit();
        break;

        case BATTLE:
        //BattleExit();
        break;

        case EXIT:
        break;
    }

    switch (gameState)
    {
        case WORLD:
        WorldStart();
        break;

        case MENU:
        //MenuStart();
        break;

        case BATTLE:
        //BattleStart();
        break;

        case EXIT:
        break;
    }

    gameState = newState;
}