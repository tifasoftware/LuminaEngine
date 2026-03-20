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
    texIndex = r->loadTexture(textureFile);
    Texture* tex = r->getTexture(texIndex);
    charHeight = tex->get_sprite_height() / 4;
    charWidth = tex->get_sprite_width() / 4;

    sprite = new CharacterSprite(texIndex, charWidth, charHeight);
}

void Character::drawCharacter(int x, int y, int mx, int my, Renderer* r)
{
    sprite->draw(x, y, mx, my, r);
    //r->drawSprite(texIndex, x - (charWidth / 2), y - (charWidth / 2));

    //if (mx > 0) dirIndex = 3;
    //if (mx < 0) dirIndex = 2;
    //if (my > 0) dirIndex = 0;
    //if (my < 0) dirIndex = 1;

    //if (mx == 0 && my == 0) animIndex = 1;

    //r->drawSubSprite(texIndex, x - (charWidth / 2), y - (charWidth / 2), (dirIndex * charWidth), (animIndex * charHeight) , charWidth, charHeight);
}

void Character::animate(int framerate, int mx, int my)
{
    sprite->animate(framerate, mx, my);
    //if (mx == 0 && my == 0) return;
    //float timeline = ((1.0f * frame) / (1.0f * framerate));
    //animIndex = 4 * timeline;
    //frame++;
    //if (frame >= framerate)
    //{
    //    frame = 0;
    //}
}

void Character::deleteCharacterSprite() {
    if (sprite != nullptr) {
        delete sprite;
        sprite = nullptr;
    }
}