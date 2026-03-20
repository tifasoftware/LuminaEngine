#pragma once

#include <graphics/Renderer.h>

#include "graphics/sprites/charactersprite.h"

class Character 
{
    public:
    Character();
    Character(const char* biofile);
    ~Character() { deleteCharacterSprite(); }
    void animate(int framerate, int mx, int my);
    void drawCharacter(int x, int y, int mx, int my, Renderer* r);
    void loadCharacterSprite(Renderer* r);

    private:
    void deleteCharacterSprite();
    const char* characterName;
    const char* textureFile;
    int health;
    int magic;
    int level;
    CharacterSprite* sprite;
    int texIndex = -1;
    int charHeight = 32;
    int charWidth = 32;
    int dirIndex = 0;
    int animIndex = 0;
    int frame = 0;
};
