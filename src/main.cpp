#include <SDL.h>
#include <SDL_image.h>
#include <pspkernel.h>
#include <pspdisplay.h>
#include "lumina.h"

int main(int argc, char *argv[])
{
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMECONTROLLER);

    // Enable png support for SDL2_image
    IMG_Init(IMG_INIT_PNG);

    SDL_Window * window = SDL_CreateWindow(
        "window",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        480,
        272,
        0
    );

    SoundSystem* snd = new SoundSystem();
    Renderer* r = new Renderer(window);

    snd->startMusic("bgm0.ogg");

    r->loadTexture("splash.png");

    const int FRAME_RATE = 60;
    const int REDRAW_DELAY = 1000 / FRAME_RATE;

    Fade* f = new Fade(r);
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

    TileMap* tm = new TileMap("maptest.lmap", r);

    Character* lumina = new Character();

    lumina->loadCharacterSprite(r);
    int luminaX = 480 / 2;
    int luminaY = 272 / 2;

    int luminaMoveX = 0;
    int luminaMoveY = 0;

    int luminaMoveRate = 2;

    int running = 1;
    SDL_Event event;

    f->FadeIn(1.0f);

    while (running) { 
        // Process input
        if (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    // End the loop if the programs is being closed
                    running = 0;
                    break;
                case SDL_CONTROLLERDEVICEADDED:
                    // Connect a controller when it is connected
                    SDL_GameControllerOpen(event.cdevice.which);
                    break;
                case SDL_CONTROLLERBUTTONDOWN:
                    if(event.cbutton.button == SDL_CONTROLLER_BUTTON_START) {
                        // Close the program if start is pressed
                        running = 0;
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

        lumina->drawCharacter(luminaX, luminaY, r);

        if (f->isFading()){
            f->Render(1.0f / FRAME_RATE);
        }
        // Draw everything on a white background
        
        r->present();
        SDL_Delay(REDRAW_DELAY);
    }
    snd->shutdown();
    r->shutdown();
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}

