#pragma once

#include <graphics/Renderer.h>

class Character 
{
    public:
    Character();
    Character(const char* biofile);
    void drawCharacter(int x, int y, Renderer* r);
    void loadCharacterSprite(Renderer* r);

    private:
    const char* characterName;
    const char* textureFile;
    int health;
    int magic;
    int level;
    int texIndex = -1;

};