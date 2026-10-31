#pragma once
#include "secondary_activity.h"
#include "vgui/panel.h"
#include <vector>

#include "entities/monster.h"
#include "vgui/battle/char_card.h"
#include "vgui/battle/counter.h"

enum BattleStage : u_int8_t {
    BATTLESTAGE_PARTY_PROMPT,
    BATTLESTAGE_PARTY_SUBPROMPT,
    BATTLESTAGE_PARTY_RUNATTACKS,
    BATTLESTAGE_WIN_INITMESSAGE,
    BATTLESTAGE_WIN_IDLEMESSAGE,
    BATTLESTAGE_WIN_CLOSEBATTLE,
    BATTLESTAGE_MONSTER_INITMESSAGE,
    BATTLESTAGE_MONSTER_IDLEMESSAGE,
    BATTLESTAGE_MONSTER_RUNATTACKS,
    BATTLESTAGE_NEXTROUND,
    BATTLESTAGE_NOOPS
};

struct CharacterAction {
    CharacterAction(int a, int m) {
        action = a;
        modifier = m;
    }

    u_int8_t action;
    u_int8_t modifier;
};

class Battle : public SecondaryActivity {
  public:
    Battle(Renderer *r, SoundSystem *snd, GamePlayState *gps);
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
    Panel *actionPanel;
    Panel *characterPanel;
    Panel *subMenuPanel;

    int battleGlyphIndex = -1;
    int characterProfileIndex = -1;
    int skyIndex = -1;

    std::vector<CharacterCard *> chars_ui;
    std::vector<CharacterAction> actions;

    uint8_t party_size = 1;

    Monster *monster;
    BatCounter *monster_health;

    uint8_t turn = 0;

    BattleStage stage = BATTLESTAGE_PARTY_PROMPT;

    void UpdateUI();
    void runMonsterAttacks();
    void runPartyAttacks();

    void createSubMenu();
};
