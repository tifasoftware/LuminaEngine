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
}

void Character::loadCharacterSprite(Renderer* r)
{
    deleteCharacterSprite();
    int texIndex = r->loadTexture(textureFile);
    Texture* tex = r->getTexture(texIndex);
    int charHeight = tex->get_sprite_height() / 4;
    int charWidth = tex->get_sprite_width() / 4;

    sprite = new CharacterSprite(texIndex, charWidth, charHeight);
}

void Character::drawCharacter(int x, int y, int mx, int my, Renderer* r)
{
    sprite->draw(x, y, mx, my, r);
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