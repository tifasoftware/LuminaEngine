#pragma once

#include <graphics/Renderer.h>

class Character 
{
    public:
    void rawCharacter(int x, int y, Renderer* r);
    void loadCharacterSprite(Renderer* r);

    private:
    char[]* characterName;
    int health;
    int magic;
    int level;
    int texIndex;

};