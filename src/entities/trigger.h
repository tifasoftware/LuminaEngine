#pragma once
#include "entity.h"

class Trigger : public Entity{
    public:
    //virtual void trigger() = 0;
    bool isInTrigger(int charX, int charY);

    EntityType getType() override { return TRIGGER_LUA; }

    virtual ~Trigger() {}
};
