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

Monster::Monster(int type) {
    switch (type) {
    case 1:
        monsterName = "Turret";
        textureFile = "turret.png";
        actionTitle = "Gun";
        health = 100;
        difficulty = 1;
        break;

    case 0:
    default:
        monsterName = "Tree Mafia";
        textureFile = "treemafia.png";
        actionTitle = "Hit";
        health = 1000;
        difficulty = 10;
        break;
    }

    max_health = health;
    x = 0;
    y = 0;
    sprite_index = 0;
    target = 0;
    damagePoints = 0;
}

Monster::~Monster() {}

void Monster::DrawMonster(Renderer *r) {
    if (sprite_index != -1)
        r->drawSprite(sprite_index, x, y);
}

void Monster::nextAction() {
    damagePoints = LuminaUtils::RandomInt(0, 100);
    target = LuminaUtils::RandomInt(0, 4);
    // Customize Hit names later
}

void Monster::nextAction(Party *party) {
    damagePoints = LuminaUtils::RandomInt(0, 10 * difficulty);

    uint8_t party_size = party->members();
    uint8_t alive_members = party_size;
    std::vector<uint8_t> map;

    for (int i = 0; i < party_size; i++) {
        if (party->GetPartyMember(i)->GetHealth() <= 0)
            alive_members--;
        else
            map.push_back(i);
    }

    target = map[LuminaUtils::RandomInt(0, alive_members)];
}
