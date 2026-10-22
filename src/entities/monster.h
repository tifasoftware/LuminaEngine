#pragma once
#include "graphics/renderer.h"

class Monster {
  public:
    Monster();
    ~Monster();

    int LoadMonsterSprite(Renderer *r) {
        sprite_index = r->loadTexture(textureFile);
        return sprite_index;
    }
    void UnloadMonsterSprite(Renderer *r) { r->unloadTexture(sprite_index); }
    void DrawMonster(Renderer *r);

    const char *GetCharacterName() { return monsterName; }

    void Move(int nx, int ny) {
        x = nx;
        y = ny;
    }

    void nextAction();
    uint16_t getDamagePoints() { return damagePoints; }
    uint8_t getTarget() { return target; }
    const char *getActionTitle() { return actionTitle; }

    int GetHealth() { return health; }
    void Damage(int points) { health -= points; }

  private:
    int health;
    int difficulty;
    int sprite_index;

    int x;
    int y;

    const char *textureFile;
    const char *monsterName;
    const char *actionTitle;

    u_int16_t damagePoints;
    u_int8_t target;
};
