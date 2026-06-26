#include <cstdio>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>

int main(int argc, char *argv[]) {
    printf("Hello Lumina!\n");

    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMECONTROLLER);
    printf("Hello Lumina!\n");

    int r = 0;
    int g = 0;
    int b = 0;
    int s = 0;

    SDL_Window* window = SDL_CreateWindow(
        "window",
        0,
        0,
        640,
        480,
        SDL_WINDOW_FULLSCREEN
    );

    printf("Created Window!\n");

    SDL_ShowCursor(SDL_DISABLE);

    SDL_Renderer* sdl_r = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    printf("Created Renderer!\n");
    SDL_Rect screen = { 0, 0, 640, 480 };

    while (1) {
        if (s == 0) {
            r++;
            if (r >= 255) s++;
        } else if (s == 1) {
            g++;
            if (g >= 255) s++;
        } else if (s == 2) {
            b++;
            if (b >= 255) s++;
        } else if (s == 3) {
            r--;
            if (r <= 0) s++;
        } else if (s == 4) {
            g--;
            if (g <= 0) s++;
        } else if (s == 5) {
            b--;
            if (b <= 0) s = 0;
        } else {
            s = 0;
        }

        SDL_RenderClear(sdl_r);
        SDL_SetRenderDrawColor(sdl_r, 255, g, b, 255);
        SDL_RenderFillRect(sdl_r, &screen);
        SDL_RenderPresent(sdl_r);
        SDL_Delay(1000);
        printf("Drew Frame!\n");
    }

    return 0;
}
