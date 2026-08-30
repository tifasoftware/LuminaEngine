#pragma once
#include "secondary_activity.h"

class Battle : public SecondaryActivity {
    public:
    Battle(Renderer* r, SoundSystem* snd, GamePlayState* gps);
    ~Battle() override = default;
};