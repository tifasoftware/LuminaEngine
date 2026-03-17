#pragma once
#include "entity.h"

class Trigger : public Entity{
    public:
    virtual void trigger() = 0;
    bool isInTrigger();

    ~Trigger();
};
