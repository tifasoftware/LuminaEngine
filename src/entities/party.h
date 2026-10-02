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
    int members() { return static_cast<int>(party.size()); }

    private:
    std::vector<Character*> party;
};
