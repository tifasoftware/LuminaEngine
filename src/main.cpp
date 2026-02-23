#include <SDL.h>
#include <SDL_image.h>
#include <pspkernel.h>
#include <pspdisplay.h>
#include <graphics/Renderer.h>
#include <graphics/Texture.h>
#include <graphics/TileMap.h>

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
    r->clear();
    r->drawSprite(0, 0, 0);
    r->present();

    SDL_Delay(3000);

    r->unloadAllTextures();

    r->clear();
    r->present();

    SDL_Delay(1000);

    TileMap* tm = new TileMap(r);

    int running = 1;
    SDL_Event event;
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

        // Draw everything on a white background
        
        r->present();
    }
    r->shutdown();
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}

