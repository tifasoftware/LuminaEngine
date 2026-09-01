#include "battle.h"

#include "vgui/button.h"
#include "vgui/glyph.h"
#include "vgui/imagebox.h"
#include "vgui/text.h"
#include "vgui/battle/counter.h"

Battle::Battle(Renderer* r, SoundSystem* snd, GamePlayState* gps) : SecondaryActivity(r, snd, gps) {
    actionPanel = new Panel(r, r->GetWidth() - 103, r->GetHeight() - 113, 100, 110);

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
    characterPanel = new Panel(r, 3, r->GetHeight() - 113, r->GetWidth() - 109, 110);

    battleGlyphIndex = renderer->loadTexture("battleglyphs.png");
    characterProfileIndex = renderer->loadTexture("lumina_dialog.png");

    Glyph* g1 = new Glyph();
    g1->setAtlas(battleGlyphIndex);
    g1->setGlyph(16, 16, 16, 8);

    Glyph* g2 = new Glyph();
    g2->setAtlas(battleGlyphIndex);
    g2->setGlyph(16, 24, 16, 8);

    BatCounter* bc = new BatCounter(battleGlyphIndex, 100,300);
    BatCounter* bc2 = new BatCounter(battleGlyphIndex, 12,30);

    ImageBox* profile = new ImageBox();
    profile->setTexture(characterProfileIndex);

    Text* text = new Text("Lumina", SYSTEX_FONT_REG);
    //text->SetFGColor(255,0,0);

    characterPanel->addElement(profile, 4, 20);
    characterPanel->addElement(text, 4,2);

    characterPanel->addElement(g1, 2, 90);
    characterPanel->addElement(bc, 14, 90);
    characterPanel->addElement(g2, 2, 100);
    characterPanel->addElement(bc2, 14, 100);


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
