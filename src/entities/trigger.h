#pragma once

class Trigger {
    public:
    virtual void trigger() = 0;
    bool isInTrigger();

    protected:
    int x;
    int y;
    int w;
    int h;
};