#include "battle.h"

#include "vgui/button.h"
#include "vgui/glyph.h"
#include "vgui/imagebox.h"
#include "vgui/text.h"
#include "vgui/battle/char_card.h"
#include "vgui/battle/counter.h"
#include "vgui/overlays/messagebox.h"

Battle::Battle(Renderer* r, SoundSystem* snd, GamePlayState* gps) : SecondaryActivity(r, snd, gps) {
    skyIndex = renderer->loadTexture("battlesky.png");

    actionPanel = new Panel(r, r->GetWidth() - 103, r->GetHeight() - 113, 100, 110);

    // Initialize Action Panel
    Button* btnF = new Button("<i>InstaKill</>", "quitbattle", SYSTEX_FONT_REG);
    Button* btnAttack = new Button("Attack", "attack", SYSTEX_FONT_REG);
    Button* btnMagic = new Button("Magic", "magic", SYSTEX_FONT_REG);
    Button* btnGuard = new Button("Guard", "guard", SYSTEX_FONT_REG);
    Button* btnItems = new Button("Items", "items", SYSTEX_FONT_REG);

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
    monster->Move(renderer->GetWidth() / 2 - 64, renderer->GetHeight() / 2 - 128);

    //Initialize Character Panel
    characterPanel = new Panel(r, 3, r->GetHeight() - 113, r->GetWidth() - 109, 110);

    battleGlyphIndex = renderer->loadTexture("battleglyphs.png");

    Party* party = gps->party;

    int size = gps->party->members();
    if (size > 5) size = 5;

    party_size = size;

    for (int i = 0; i < size; i++) {
        Character* c = party->GetPartyMember(i);

        characterProfileIndex = c->loadCharacterProfile(renderer);

        CharacterCard* cc = new CharacterCard(battleGlyphIndex,
            characterProfileIndex,
            c->GetCharacterName());

        cc->setHealth(c->GetHealth());
        cc->setMaxHealth(c->GetMaxHealth());
        cc->setMagic(c->GetMagic());
        cc->setMaxMagic(c->GetMaxMagic());

        characterPanel->addElement(cc, 2 + (70 * i), 2);
        chars_ui.push_back(cc);
    }

    if (!chars_ui.empty()) chars_ui[0]->setActive(true);

    btnAttack->startFocus();
}

void Battle::render() {
    if (skyIndex != -1) renderer->fillTile(skyIndex);
    monster->DrawMonster(renderer);

    Overlay* o = gps->GetOverlay();
    if (o == nullptr || !o->isEngaged()) {
        if (stage == 0) actionPanel->Render();
        characterPanel->Render();
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
    Button* selB = dynamic_cast<Button*>(actionPanel->focusedElement());

    if (selB != nullptr)
    {
        if (selB->GetTag() == "quitbattle")
        {
            stage = 1;
        } else {
            turn++;
            if (turn >= party_size) {
                runMonsterAttacks();
            } else UpdateUI();
        }
    }
}

void Battle::OnButtonB() {
    if (turn < 0) turn--;
    UpdateUI();
}

void Battle::OnButtonUp() {
    if (actionPanel->focusedElement() != nullptr) {
        actionPanel->focusedElement()->giveFocusUp();
            //soundSystem->playSFX(clink);
    }
}

void Battle::OnButtonLeft() {

}

void Battle::OnButtonRight() {

}

void Battle::OnButtonDown() {
    if (actionPanel->focusedElement() != nullptr) {
        actionPanel->focusedElement()->giveFocusDown();
        //soundSystem->playSFX(clink);
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
    //soundSystem->playSFX(cwhime);
    if (stage == 1) {
        gps->RequestChangeMusic("victory.ogg");
        MessageBox* o = new MessageBox(renderer, this);
        o->DisplayDialogue("Your party has won!");
        gps->DispatchOverlay(o);
        stage = 2;
    } else if (stage == 2) {
        Overlay* o = gps->GetOverlay();
        if (o != nullptr) {
            if (!o->isEngaged()) stage = 3;
        }
    }
    else if (stage == 3) {
        stage = 4;
        gps->RequestSwitchState(WORLD);
    } else if (stage == 5) {
        MessageBox* o = new MessageBox(renderer, this);
        char combine[256];
        strcpy(combine, monster->GetCharacterName());
        strcat(combine, " Uses <i>");
        strcat(combine, monster->getActionTitle());
        strcat(combine, "</> against ");
        strcat(combine, gps->party->GetPartyMember(monster->getTarget())->GetCharacterName());
        o->DisplayDialogue(combine);
        gps->DispatchOverlay(o);
        stage = 6;
    } else if (stage == 6) {
        Overlay* o = gps->GetOverlay();
        if (o != nullptr) {
            if (!o->isEngaged()) {
                stage = 7;
            }
        }
    } else if (stage == 7) {
        bool advance = true;
        for (int i = 0; i < party_size; i++) {
            BatCounter* b = chars_ui[i]->getHPCounter();
            b->animate();
            if (b->inAnimation()) advance = false;
        }
        if (advance) stage = 8;
    } else if (stage == 8) {
        stage = 0;
        turn = 0;
        UpdateUI();
    }
}

void Battle::runMonsterAttacks() {
    UpdateUI();
    monster->nextAction();
    int target = monster->getTarget();

    BatCounter* b = chars_ui[target]->getHPCounter();
    b->slideValue(gps->party->GetPartyMember(target)->GetHealth() - monster->getDamagePoints(), 30);

    gps->party->GetPartyMember(target)->Hurt(monster->getDamagePoints());

    stage = 5;
}
