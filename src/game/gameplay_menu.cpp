#include <game/gameplay.h>

void GamePlay::MenuStart()
{
    clink = snd->loadSFX("hover.wav");
    chime = snd->loadSFX("select.wav");
    fontAtlas = r->loadTexture("fontatlas.png");
    text = new Text("Main Menu", fontAtlas, 0, 0);
    text->SetFGColor(0,100,255);
    

    f->FadeIn(0.5f);

    while (f->isFading())
    {
        r->clear();

        text->Render(r);
        // Draw everything on a white background
        
        if (f->isFading()){
            f->Render(1.0f / FRAME_RATE);
        }

        r->present();
        
        SDL_Delay(REDRAW_DELAY);
    }

    inTransition = false;
}

void GamePlay::MenuDraw()
{
    if (inTransition) return;
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
                        // Close the program if start is pressed
                        snd->playSFX(chime);
                        RequestSwitchState(WORLD);
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

        //if (text != nullptr)
        text->Render(r);
        // Draw everything on a white background
        
        r->present();
        if (wantNewState) SwitchState();
}

void GamePlay::MenuExit()
{
    inTransition = true;

    f->FadeOut(0.5f);

    while (f->isFading())
    {
        r->clear();

        text->Render(r);
        // Draw everything on a white background
        
        if (f->isFading()){
            f->Render(1.0f / FRAME_RATE);
        }

        r->present();
        SDL_Delay(REDRAW_DELAY);
    }

    snd->unloadAllSFX();
    r->unloadAllTextures();

    delete text;
    text = nullptr;
}