#pragma once
#include "secondary_activity.h"
#include "vgui/panel.h"
#include <vector>

#include "entities/monster.h"
#include "vgui/battle/char_card.h"

class Battle : public SecondaryActivity {
    public:
    Battle(Renderer* r, SoundSystem* snd, GamePlayState* gps);
    ~Battle() override;

    void render() override;
    void update() override;

    void OnButtonA() override;
    void OnButtonB() override;
    void OnButtonUp() override;
    void OnButtonDown() override;
    void OnButtonLeft() override;
    void OnButtonRight() override;

    private:
    Panel* actionPanel;
    Panel* characterPanel;

    int battleGlyphIndex = -1;
    int characterProfileIndex = -1;

    std::vector<CharacterCard*> chars_ui;
    uint8_t party_size = 1;

    Monster* monster;

    uint8_t turn = 0;

    uint8_t stage = 0;

    void UpdateUI();
    void runMonsterAttacks();
};
