#include <graphics/Renderer.h>
#include <vgui/text.h>

Text::Text(const char* t, int fti, int _x, int _y)
{
    text = t;
    fontTexIndex = fti;
    x = _x;
    y = _y;
}

void Text::Render(Renderer* r)
{
    SDL_SetTextureColorMod(r->getTexture(fontTexIndex)->get_SDLTex(), fg_r, fg_g, fg_b);
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

        r->drawSubSprite(fontTexIndex, x + oX, y + oY, cX, cY, cW, cH);

        if (c == '\n')
        {
            oX = 0;
            oY += 16;
        } else {
            oX += 8;
        } 
    }
    SDL_SetTextureColorMod(r->getTexture(fontTexIndex)->get_SDLTex(), 255, 255, 255);
}

void Text::SetFGColor(int r, int g, int b)
{
    fg_r = r;
    fg_g = g;
    fg_b = b;
}