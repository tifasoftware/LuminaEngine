#include "party.h"

Party::Party() {
    party.push_back(new Character(0));
    party.push_back(new Character(1));
    party.push_back(new Character(2));
    party.push_back(new Character(3));
    party.push_back(new Character(4));
}

Party::~Party() {
    //Save CPU Time on static_cast
    int size = static_cast<int>(party.size());

    //Deconstruct characters in party
    for (int i = 0; i < size; i++) {
        delete party[i];
    }
}

int Party::AddCharacter(Character *chr) {
    party.push_back(chr);
    return static_cast<int>(party.size()) - 1;
}

int Party::FindCharacter(const char *name) {
    //Save CPU Time on static_cast
    int size = static_cast<int>(party.size());

    for (int i = 0; i < size; i++) {
        Character* chr = party[i];

        if (strcmp(chr->GetCharacterName(), name) == 0) {
            return i;
        }
    }

    return -1;
}
