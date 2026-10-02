#pragma once
#include "character.h"

class Party {
public:
    Party();
    ~Party();

    Character* GetPartyMember(int index) { return party[index]; }
    int AddCharacter(Character* chr);
    //void RemoveCharacter(int index);
    int FindCharacter(const char* name);

    private:
    std::vector<Character*> party;
};
