#include "monster.h"

#include "common/utils.h"

Monster::Monster() {
    monsterName = "Tree Mafia";
    textureFile = "treemafia.png";
    actionTitle = "Hit";
    health = 100;
    difficulty = 1;

    x = 0;
    y = 0;
    sprite_index = -1;
    target = 0;
    damagePoints = 0;
}

Monster::~Monster() {

}

void Monster::DrawMonster(Renderer *r) {
    if (sprite_index != -1) r->drawSprite(sprite_index, x, y);
}

void Monster::nextAction() {
    damagePoints = LuminaUtils::RandomInt(0,20);
    target = LuminaUtils::RandomInt(0,4);
    //Customize Hit names later
}
