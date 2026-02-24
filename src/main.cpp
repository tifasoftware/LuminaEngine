#include <SDL.h>
#include <SDL_image.h>
#include <pspkernel.h>
#include <pspdisplay.h>
#include <graphics/Renderer.h>
#include <graphics/Texture.h>
#include <graphics/TileMap.h>
#include <graphics/effects/fade.h>
#include <entities/character.h>

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

    Renderer* r = new Renderer(window);

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
                    break;
            }
        }

        // Clear the screen
        r->clear();

        // Draw the 'grass' sprite
        tm->drawMap();

        lumina->drawCharacter(480 / 2, 272 / 2, r);

        if (f->isFading()){
            f->Render(1.0f / FRAME_RATE);
        }
        // Draw everything on a white background
        
        r->present();
    }
    r->shutdown();
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}

