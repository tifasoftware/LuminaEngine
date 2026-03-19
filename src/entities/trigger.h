#pragma once
#include "entity.h"

class Trigger : public Entity{
    public:
    //virtual void trigger() = 0;


    EntityType getType() override { return TRIGGER_LUA; }

    virtual ~Trigger() {}
};
