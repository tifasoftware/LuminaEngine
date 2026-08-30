#pragma once

#include "game/IControllable.h"
#include "game/gameplay_state.h"
#include "graphics/renderer.h"
#include "sound/soundsystem.h"

class SecondaryActivity : public IControllable {
    public:
    SecondaryActivity(Renderer* r, SoundSystem* snd, GamePlayState* gps);
    //virtual ~ISecondaryActivity() = default;

    virtual void render() {}

    protected:
    Renderer* renderer;
    SoundSystem* soundSystem;
    GamePlayState* gps;
};
