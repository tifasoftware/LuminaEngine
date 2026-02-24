#include <graphics/Renderer.h>
#include <graphics/Texture.h>
#include <entities/character.h>

Character::Character()
{
    characterName = "Lumina";
    textureFile = "avatar.png";
    health = 1000;
    magic = 50;
    level = 1;
}

void Character::loadCharacterSprite(Renderer* r)
{
    texIndex = r->loadTexture(textureFile);
}

void Character::drawCharacter(int x, int y, Renderer* r)
{
    r->drawSprite(texIndex, x, y);
}