#include <game/gameplay.h>

void GamePlay::WorldStart()
{
    fontAtlas = r->loadTexture("fontatlas.png");
    //text = new Text("The Quick Brown Fox Jumps Over The Lazy Dog", fontAtlas, 16, 16);

    tm->loadMap();
    lumina->loadCharacterSprite(r);

    luminaX = 480 / 2;
    luminaY = 272 / 2;

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

        if (!tm->isColliding(luminaX + luminaMoveX, luminaY + luminaMoveY)){
            luminaX += luminaMoveX;
            luminaY += luminaMoveY;
        }
        // Clear the screen
        r->clear();

        // Draw the 'grass' sprite
        tm->drawMap();

        //text->Render(r);

        lumina->drawCharacter(luminaX, luminaY, r);

        if (f->isFading()){
            f->Render(1.0f / FRAME_RATE);
        }
        // Draw everything on a white background
        
        r->present();
        if (wantNewState) SwitchState();
}

void GamePlay::WorldExit()
{
    inTransition = true;
    f->FadeOut(0.5f);

    while (f->isFading())
    {
        r->clear();

        // Draw the 'grass' sprite
        tm->drawMap();

        //text->Render(r);

        lumina->drawCharacter(luminaX, luminaY, r);

        if (f->isFading()){
            f->Render(1.0f / FRAME_RATE);
        }
        // Draw everything on a white background
        
        r->present();
        SDL_Delay(REDRAW_DELAY);
    }

    //tm->disposeMap();
    
    r->unloadAllTextures();

    //delete text;
}



