#include "battle.h"

#include "vgui/battle/char_card.h"
#include "vgui/battle/counter.h"
#include "vgui/button.h"
#include "vgui/glyph.h"
#include "vgui/imagebox.h"
#include "vgui/overlays/messagebox.h"
#include "vgui/overlays/question.h"
#include "vgui/text.h"

Battle::Battle(Renderer *r, SoundSystem *snd, GamePlayState *gps)
    : SecondaryActivity(r, snd, gps) {
    skyIndex = renderer->loadTexture("battlesky.png");

    subMenuPanel = nullptr;

    actionPanel =
        new Panel(r, r->GetWidth() - 103, r->GetHeight() - 113, 100, 110);

    // Initialize Action Panel
    Button *btnF = new Button("<i>InstaKill</>", "quitbattle", SYSTEX_FONT_REG);
    Button *btnAttack = new Button("Attack", "attack", SYSTEX_FONT_REG);
    Button *btnMagic = new Button("Magic", "magic", SYSTEX_FONT_REG);
    Button *btnGuard = new Button("Guard", "guard", SYSTEX_FONT_REG);
    Button *btnItems = new Button("Items", "items", SYSTEX_FONT_REG);

    actionPanel->addElement(btnF, 4, 84);
    actionPanel->addElement(btnAttack, 4, 4);
    actionPanel->addElement(btnMagic, 4, 24);
    actionPanel->addElement(btnGuard, 4, 44);
    actionPanel->addElement(btnItems, 4, 64);

    btnAttack->addLowerElement(btnMagic);
    btnMagic->addUpperElement(btnAttack);

    btnMagic->addLowerElement(btnGuard);
    btnGuard->addUpperElement(btnMagic);

    btnGuard->addLowerElement(btnItems);
    btnItems->addUpperElement(btnGuard);

    btnItems->addLowerElement(btnF);
    btnF->addUpperElement(btnItems);

    monster = new Monster();
    monster->LoadMonsterSprite(renderer);
    monster->Move(renderer->GetWidth() / 2 - 64,
                  renderer->GetHeight() / 2 - 128);

    // Initialize Character Panel
    characterPanel =
        new Panel(r, 3, r->GetHeight() - 113, r->GetWidth() - 109, 110);

    battleGlyphIndex = renderer->loadTexture("battleglyphs.png");

    monster_health = new BatCounter(battleGlyphIndex, 100, 100);
    monster_health->move(renderer->GetWidth() / 2 - 32,
                         renderer->GetHeight() / 2);

    Party *party = gps->party;

    int size = gps->party->members();
    if (size > 5)
        size = 5;

    party_size = size;

    for (int i = 0; i < size; i++) {
        Character *c = party->GetPartyMember(i);

        characterProfileIndex = c->loadCharacterProfile(renderer);

        CharacterCard *cc = new CharacterCard(
            battleGlyphIndex, characterProfileIndex, c->GetCharacterName());

        cc->setHealth(c->GetHealth());
        cc->setMaxHealth(c->GetMaxHealth());
        cc->setMagic(c->GetMagic());
        cc->setMaxMagic(c->GetMaxMagic());

        characterPanel->addElement(cc, 2 + (70 * i), 2);
        chars_ui.push_back(cc);
    }

    if (!chars_ui.empty())
        chars_ui[0]->setActive(true);

    btnAttack->startFocus();
}

void Battle::render() {
    if (skyIndex != -1)
        renderer->fillTile(skyIndex);
    monster->DrawMonster(renderer);

    Overlay *o = gps->GetOverlay();
    if (o == nullptr || !o->isEngaged()) {
        if (stage == BATTLESTAGE_PARTY_PROMPT)
            actionPanel->Render();
        if (stage == BATTLESTAGE_PARTY_SUBPROMPT) {
            if (subMenuPanel != nullptr) {
                subMenuPanel->Render();
            } else
                stage = BATTLESTAGE_PARTY_PROMPT;
        } else
            characterPanel->Render();
    }
    if (stage == BATTLESTAGE_PARTY_RUNATTACKS) {
        monster_health->render(renderer);
    }
}

Battle::~Battle() {
    actionPanel->destroy();
    characterPanel->destroy();
    delete actionPanel;
    delete characterPanel;
    delete monster;
}

void Battle::OnButtonA() {
    if (stage == BATTLESTAGE_PARTY_PROMPT) {
        Button *selB = dynamic_cast<Button *>(actionPanel->focusedElement());

        if (selB != nullptr) {
            if (selB->CompareTag("quitbattle") == 0) {
                stage = BATTLESTAGE_WIN_INITMESSAGE;
            } else {

                if (selB->CompareTag("attack") == 0) {
                    actions.push_back(CharacterAction(0, 0));
                    turn++;
                } else if (selB->CompareTag("guard") == 0) {
                    actions.push_back(CharacterAction(1, 0));
                    turn++;
                } else {
                    actions.push_back(CharacterAction(2, 0));
                    createSubMenu();
                    stage = BATTLESTAGE_PARTY_SUBPROMPT;
                }

                if (turn >= party_size) {
                    runMonsterAttacks();
                } else
                    UpdateUI();
            }
        }
    } else if (stage == BATTLESTAGE_PARTY_SUBPROMPT) {
        Button *selB = dynamic_cast<Button *>(subMenuPanel->focusedElement());

        if (selB != nullptr) {
            if (selB->CompareTag("btn1") == 0) {
                actions[actions.size() - 1].modifier = 1;
            } else if (selB->CompareTag("btn2") == 0) {
                actions[actions.size() - 1].modifier = 2;
            } else if (selB->CompareTag("btn3") == 0) {
                actions[actions.size() - 1].modifier = 3;
            } else if (selB->CompareTag("btn4") == 0) {
                actions[actions.size() - 1].modifier = 4;
            }

            turn++;
            stage = BATTLESTAGE_PARTY_PROMPT;

            if (turn >= party_size) {
                runMonsterAttacks();
            } else
                UpdateUI();
        }
    }
}

void Battle::OnButtonB() {
    if (stage == BATTLESTAGE_PARTY_PROMPT) {
        if (turn < 0)
            turn--;
        UpdateUI();
    } else if (stage == BATTLESTAGE_PARTY_SUBPROMPT) {
        actions.pop_back();
        stage = BATTLESTAGE_PARTY_PROMPT;
    }
}

void Battle::OnButtonUp() {
    if (actionPanel->focusedElement() != nullptr) {
        actionPanel->focusedElement()->giveFocusUp();
        // soundSystem->playSFX(clink);
    }
}

void Battle::OnButtonLeft() {}

void Battle::OnButtonRight() {}

void Battle::OnButtonDown() {
    if (actionPanel->focusedElement() != nullptr) {
        actionPanel->focusedElement()->giveFocusDown();
        // soundSystem->playSFX(clink);
    }
}

void Battle::UpdateUI() {
    for (int i = 0; i < chars_ui.size(); i++) {
        chars_ui[i]->setActive(i == turn);
        chars_ui[i]->setHealth(gps->party->GetPartyMember(i)->GetHealth());
        chars_ui[i]->setMagic(gps->party->GetPartyMember(i)->GetMagic());
    }
}

void Battle::update() {
    // soundSystem->playSFX(cwhime);
    if (stage == BATTLESTAGE_WIN_INITMESSAGE) {
        gps->RequestChangeMusic("victory.ogg");
        MessageBox *o = new MessageBox(renderer, this);
        o->DisplayDialogue("Your party has won!");
        gps->DispatchOverlay(o);
        stage = BATTLESTAGE_WIN_IDLEMESSAGE;
    } else if (stage == BATTLESTAGE_WIN_IDLEMESSAGE) {
        Overlay *o = gps->GetOverlay();
        if (o != nullptr) {
            if (!o->isEngaged())
                stage = BATTLESTAGE_WIN_CLOSEBATTLE;
        }
    } else if (stage == BATTLESTAGE_WIN_CLOSEBATTLE) {
        stage = BATTLESTAGE_NOOPS;
        gps->RequestSwitchState(WORLD);
    } else if (stage == BATTLESTAGE_MONSTER_INITMESSAGE) {
        MessageBox *o = new MessageBox(renderer, this);
        char combine[256];
        strcpy(combine, monster->GetCharacterName());
        strcat(combine, " Uses <i>");
        strcat(combine, monster->getActionTitle());
        strcat(combine, "</> against ");
        strcat(combine, gps->party->GetPartyMember(monster->getTarget())
                            ->GetCharacterName());
        o->DisplayDialogue(combine);
        gps->DispatchOverlay(o);
        stage = BATTLESTAGE_MONSTER_IDLEMESSAGE;
    } else if (stage == BATTLESTAGE_MONSTER_IDLEMESSAGE) {
        Overlay *o = gps->GetOverlay();
        if (o != nullptr) {
            if (!o->isEngaged()) {
                stage = BATTLESTAGE_MONSTER_RUNATTACKS;
            }
        }
    } else if (stage == BATTLESTAGE_MONSTER_RUNATTACKS) {
        bool advance = true;
        for (int i = 0; i < party_size; i++) {
            BatCounter *b = chars_ui[i]->getHPCounter();
            b->animate();
            if (b->inAnimation())
                advance = false;
        }
        if (advance)
            runPartyAttacks();
    } else if (stage == BATTLESTAGE_NEXTROUND) {
        actions.clear();

        stage = BATTLESTAGE_PARTY_PROMPT;
        turn = 0;

        UpdateUI();
    } else if (stage == BATTLESTAGE_PARTY_RUNATTACKS) {
        monster_health->animate();
        if (!monster_health->inAnimation()) {
            if (monster->GetHealth() <= 0) {
                stage = BATTLESTAGE_WIN_INITMESSAGE;
            } else if (turn >= party_size - 1) {
                turn = 0;
                stage = BATTLESTAGE_NEXTROUND;
            } else {
                turn++;

                if (actions[turn].action == 0) {
                    monster->Damage(10);
                    monster_health->slideValue(monster->GetHealth(), 30);
                }
                UpdateUI();
            }
        }
    }
}

void Battle::runMonsterAttacks() {
    UpdateUI();
    monster->nextAction();
    int target = monster->getTarget();

    BatCounter *b = chars_ui[target]->getHPCounter();
    b->slideValue(gps->party->GetPartyMember(target)->GetHealth() -
                      monster->getDamagePoints(),
                  30);

    if (actions[target].action != 1)
        gps->party->GetPartyMember(target)->Hurt(monster->getDamagePoints());

    stage = BATTLESTAGE_MONSTER_INITMESSAGE;
}

void Battle::runPartyAttacks() {
    turn = 0;
    stage = BATTLESTAGE_PARTY_RUNATTACKS;

    // TODO Condense with the other party attacks
    if (actions[0].action == 0) {
        monster->Damage(10);
        monster_health->slideValue(monster->GetHealth(), 30);
    }

    UpdateUI();
}

void Battle::createSubMenu() {

    if (subMenuPanel != nullptr) {
        subMenuPanel->destroy();
        delete subMenuPanel;
    }

    subMenuPanel = new Panel(renderer, 3, renderer->GetHeight() - 113,
                             renderer->GetWidth() - 3, 110);

    Button *b = new Button("btn1", "btn1", SYSTEX_FONT_REG);
    subMenuPanel->addElement(b, 3, 3);
    b->startFocus();
}
