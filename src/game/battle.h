#pragma once
#include "secondary_activity.h"
#include "vgui/panel.h"

class Battle : public SecondaryActivity {
    public:
    Battle(Renderer* r, SoundSystem* snd, GamePlayState* gps);
    ~Battle() override;

    void render() override;

    void OnButtonA() override;
    void OnButtonUp() override;
    void OnButtonDown() override;
    void OnButtonLeft() override;
    void OnButtonRight() override;

    private:
    Panel* actionPanel;
    Panel* characterPanel;
};
