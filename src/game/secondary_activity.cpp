#include "secondary_activity.h"

SecondaryActivity::SecondaryActivity(Renderer *r, SoundSystem *snd, GamePlayState *gps) {
    renderer = r;
    soundSystem = snd;
    this->gps = gps;
}