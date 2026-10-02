#include "battle.h"

#include "vgui/button.h"
#include "vgui/glyph.h"
#include "vgui/imagebox.h"
#include "vgui/text.h"
#include "vgui/battle/char_card.h"
#include "vgui/battle/counter.h"
#include "vgui/overlays/messagebox.h"

Battle::Battle(Renderer* r, SoundSystem* snd, GamePlayState* gps) : SecondaryActivity(r, snd, gps) {
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

    //Initialize Character Panel
    characterPanel = new Panel(r, 3, r->GetHeight() - 113, r->GetWidth() - 109, 110);

    battleGlyphIndex = renderer->loadTexture("battleglyphs.png");

    Party* party = gps->party;

    int size = gps->party->members();
    if (size > 5) size = 5;

    for (int i = 0; i < size; i++) {
        Character* c = party->GetPartyMember(i);

        characterProfileIndex = c->loadCharacterProfile(renderer);

        CharacterCard* cc = new CharacterCard(battleGlyphIndex,
            characterProfileIndex,
            c->GetCharacterName());

        cc->setHealth(c->GetHealth());
        //cc->setMagic()

        characterPanel->addElement(cc, 2 + (70 * i), 2);
        chars_ui.push_back(cc);
    }

    if (!chars_ui.empty()) chars_ui[0]->setActive(true);

    btnAttack->startFocus();
}

void Battle::render() {
    Overlay* o = gps->GetOverlay();
    if (o == nullptr || !o->isEngaged()) {
        actionPanel->Render();
        characterPanel->Render();
    }
}

Battle::~Battle() {
    actionPanel->destroy();
    characterPanel->destroy();
    delete actionPanel;
    delete characterPanel;
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
            if (turn >= chars_ui.size()) {
                turn = 0;
            }
            UpdateUI();
        }
    }
}

void Battle::OnButtonB() {
    turn--;
    if (turn >= chars_ui.size()) {
        turn = chars_ui.size() - 1;
    }
    chars_ui[0]->setHealth(turn);
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
    }
}
