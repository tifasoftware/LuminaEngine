#include "battle.h"

#include "vgui/button.h"

Battle::Battle(Renderer* r, SoundSystem* snd, GamePlayState* gps) : SecondaryActivity(r, snd, gps) {
    actionPanel = new Panel(r, 3, r->GetHeight() - 103, r->GetWidth() - 6, 100);

    Button* btn = new Button("<i>Forfeit</>", "quitbattle", SYSTEX_FONT_REG);
    actionPanel->addElement(btn, 0, 0);

    btn->startFocus();
}

void Battle::render() {
    actionPanel->Render();
}

Battle::~Battle() {
    actionPanel->destroy();
    delete actionPanel;
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

}

void Battle::OnButtonLeft() {

}

void Battle::OnButtonRight() {

}

void Battle::OnButtonDown() {

}
