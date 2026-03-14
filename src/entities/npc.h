#pragma once
#include "interactable.h"


class NPC : public Interactable {
public:
    const char* GetName() { return name; }


private:
    const char* name;

};
