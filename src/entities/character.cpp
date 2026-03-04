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
}

void Character::loadCharacterSprite(Renderer* r)
{
    texIndex = r->loadTexture(textureFile);
    Texture* tex = r->getTexture(texIndex);
    charHeight = tex->get_sprite_height() / 4;
    charWidth = tex->get_sprite_width() / 4;
}

void Character::drawCharacter(int x, int y, int mx, int my, Renderer* r)
{
    //r->drawSprite(texIndex, x - (charWidth / 2), y - (charWidth / 2));

    if (mx > 0) dirIndex = 3;
    if (mx < 0) dirIndex = 2;
    if (my > 0) dirIndex = 0;
    if (my < 0) dirIndex = 1;

    r->drawSubSprite(texIndex, x - (charWidth / 2), y - (charWidth / 2), (dirIndex * charWidth), 0, charWidth, charHeight);
}