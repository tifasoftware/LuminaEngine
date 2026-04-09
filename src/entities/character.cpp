#include <graphics/Renderer.h>
#include <graphics/Texture.h>
#include <entities/character.h>

Character::Character()
{
    characterName = "Lumina";
    textureFile = "lumina.png";
    health = 1000;
    magic = 50;
    level = 1;
    sprite = nullptr;

    charWidth = 32;
    charHeight = 32;
}

void Character::loadCharacterSprite(Renderer* r)
{
    deleteCharacterSprite();
    int texIndex = r->loadTexture(textureFile);
    Texture* tex = r->getTexture(texIndex);
    charHeight = tex->get_sprite_height() / 4;
    charWidth = tex->get_sprite_width() / 4;

    sprite = new CharacterSprite(texIndex, charWidth, charHeight);
}

void Character::drawCharacter(int x, int y, int mx, int my, Renderer* r)
{
    sprite->draw(x, y, mx, my, r);

#ifdef USER_LIGHTNING
    SDL_Rect rec = {getLeftX(x), getTopY(y), charWidth, charHeight};

    SDL_SetRenderDrawBlendMode(r->getRenderer(), SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(r->getRenderer(), 255, 0, 170, 100);

    SDL_RenderFillRect(r->getRenderer(), &rec);

    SDL_SetRenderDrawBlendMode(r->getRenderer(), SDL_BLENDMODE_NONE);
#endif
}

void Character::animate(int framerate, int mx, int my)
{
    sprite->animate(framerate, mx, my);
}

void Character::deleteCharacterSprite() {
    if (sprite != nullptr) {
        delete sprite;
        sprite = nullptr;
    }
}