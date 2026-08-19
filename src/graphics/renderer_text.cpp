#include <graphics/renderer.h>
#include <graphics/texture.h>

int Renderer::drawPlainText(const char *text, int x, int y, int font, int r, int g, int b) {
    SDL_SetTextureColorMod(getTexture(font)->get_SDLTex(), r, g, b);
    int oX = 0;
    int oY = 0;

    for (int i = 0; text[i] != '\0'; i++)
    {
        char c = text[i];

        const int cW = 8;
        const int cH = 16;

        int index = c - ' ';

        int charX = index % 16;
        int charY = index / 16;

        int cX = cW * charX;
        int cY = cH * charY;

        drawSubSprite(font, x + oX, y + oY, cX, cY, cW, cH);

        if (c == '\n')
        {
            oX = 0;
            oY += 16;
        } else {
            oX += 8;
        }
    }
    SDL_SetTextureColorMod(getTexture(font)->get_SDLTex(), 255, 255, 255);

    return 0;
}

int Renderer::drawLTLText(CompiledLTL *ltl, int font, int x, int y) {
    return drawLTLText(ltl, font, x, y, -1, -1);
}

int Renderer::drawLTLText(CompiledLTL* ltl, int font, int x, int y, int start, int stop) {
    int cfont = font;

    for (int i = 0; i < 4; i++) SDL_SetTextureColorMod(getTexture(font + i)->get_SDLTex(), 200, 200, 200);

    int skip = start;
    int pchar = 0;

    int oX = 0;
    int oY = 0;

    for (int lchar = 0; ((!ltl->isEmpty(lchar)) && ((pchar <= stop) || stop == -1)); lchar++) {
        if (ltl->isChar(lchar)) {
            char c = ltl->getChar(lchar);

            const int cW = 8;
            const int cH = 16;

            int index = c - ' ';

            int charX = index % 16;
            int charY = index / 16;

            int cX = cW * charX;
            int cY = cH * charY;

            if (skip <= 0) {
                drawSubSprite(cfont, x + oX, y + oY, cX, cY, cW, cH);

                if (c == '\n')
                {
                    oX = 0;
                    oY += 16;
                } else {
                    oX += 8;
                }
                pchar++;
            } else {
                skip--;
            }
        } else {
            cfont = ltl->getFont(lchar) + font;
            Color col = ltl->getColor(lchar);
            for (int i = 0; i < 4; i++) SDL_SetTextureColorMod(getTexture(font + i)->get_SDLTex(), col.r, col.g, col.b);
        }
    }

    for (int i = 0; i < 4; i++) SDL_SetTextureColorMod(getTexture(font + i)->get_SDLTex(), 255, 255, 255);
    return 0;
}
