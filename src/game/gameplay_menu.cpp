#include <game/gameplay.h>

void GamePlay::MenuStart()
{
    clink = snd->loadSFX("hover.wav");
    chime = snd->loadSFX("select.wav");
    fontAtlas = r->loadTexture("fontatlas.png");
    panel = new Panel(r, 300, 200);

    Button* b1 = new Button("Resume", "resume", fontAtlas);
    Button* b2 = new Button("Quit", "quit", fontAtlas);

    b1->addLowerElement(b2);
    b2->addUpperElement(b1);

    panel->addElement(b1, 4, 4);
    panel->addElement(b2, 4, 24);

    b1->startFocus();

    f->FadeIn(0.5f);

    while (f->isFading())
    {
        r->clear();

        panel->Render();
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
                        if (panel->focusedElement() != nullptr)
                        {
                            if (panel->focusedElement()->giveFocusUp()) snd->playSFX(clink);
                        }
                    }
                    else if (event.cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_DOWN) {
                        if (panel->focusedElement() != nullptr)
                        {
                            if (panel->focusedElement()->giveFocusDown()) snd->playSFX(clink);
                        }
                    }
                    else if (event.cbutton.button == SDL_CONTROLLER_BUTTON_A) {
                        Button* selB = dynamic_cast<Button*>(panel->focusedElement());
                        
                        if (selB != nullptr)
                        {
                            if (selB->GetTag() == "resume")
                            {
                                snd->playSFX(chime);
                                RequestSwitchState(WORLD);
                            } 
                            else if (selB->GetTag() == "quit")
                            {
                                snd->playSFX(chime);
                                RequestSwitchState(EXIT);
                            }
                        }
                    }
                    break;
                case SDL_CONTROLLERBUTTONUP:
                    break;
            }
        }

        // Clear the screen
        r->clear();

        //if (text != nullptr)
        panel->Render();
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

        panel->Render();
        // Draw everything on a white background
        
        if (f->isFading()){
            f->Render(1.0f / FRAME_RATE);
        }

        r->present();
        SDL_Delay(REDRAW_DELAY);
    }

    snd->unloadAllSFX();
    r->unloadAllTextures();

    panel->destroy();
    delete panel;
    panel = nullptr;
}