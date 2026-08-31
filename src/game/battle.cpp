#include "battle.h"

#include "vgui/button.h"

Battle::Battle(Renderer* r, SoundSystem* snd, GamePlayState* gps) : SecondaryActivity(r, snd, gps) {
    actionPanel = new Panel(r, r->GetWidth() - 103, r->GetHeight() - 103, 100, 100);

    // Initialize Action Panel
    Button* btnF = new Button("<i>Forfeit</>", "quitbattle", SYSTEX_FONT_REG);
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
    characterPanel = new Panel(r, 3, r->GetHeight() - 103, r->GetWidth() - 109, 100);

    battleGlyphIndex = renderer->loadTexture("battleglyphs.png");


    btnAttack->startFocus();
}

void Battle::render() {
    actionPanel->Render();
    characterPanel->Render();
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
            //soundSystem->playSFX(chime);
            gps->RequestSwitchState(WORLD);
        }
    }
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
