#pragma once

#include <graphics/renderer.h>

#include "graphics/sprites/charactersprite.h"

class Character 
{
    public:
    Character();
    Character(int preset);
    Character(const char* biofile);
    ~Character() { deleteCharacterSprite(); }
    void animate(int framerate, int mx, int my);
    void drawCharacter(int x, int y, int mx, int my, Renderer* r);

    void loadCharacterSprite(Renderer* r);
    int loadCharacterProfile(Renderer* r);


    int GetHealth() { return health; }
    int GetCharacterProfile() { return profile_index; }
    const char* GetCharacterName() { return characterName; }

    void Heal(int points);
    void Hurt(int points);

    int getLeftX(int x) { return x - (charWidth / 2); }
    int getTopY(int y) { return y - (charHeight / 2); }

    private:
    void deleteCharacterSprite();
    const char* characterName;
    const char* textureFile;
    const char* profileFile;

    int health;
    int health_max;
    int magic;
    int magic_max;
    int level;

    int charWidth;
    int charHeight;

    CharacterSprite* sprite;
    int profile_index = -1;
};
