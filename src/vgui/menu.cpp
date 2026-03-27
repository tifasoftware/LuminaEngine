#include "menu.h"

Menu::Menu(MenuClass mc, Renderer* r, SoundSystem* snd, GamePlayState* gps) {
    for (int i = 0; i < 16; i++) {
        elements[i] = nullptr;
    }

    renderer = r;
    soundSystem = snd;
    this->gps = gps;

    clink = snd->loadSFX("hover.wav");
    chime = snd->loadSFX("select.wav");
    fontAtlas = r->loadTexture("fontatlas.png");
    panel = new Panel(r, 300, 200);

    switch (mc) {
        case MAIN_MENU:
            break;
        case PAUSE_MENU: {
            Button* b1 = new Button("Resume", "resume", fontAtlas);
            Button* b2 = new Button("Quit", "quit", fontAtlas);

            b1->addLowerElement(b2);
            b2->addUpperElement(b1);

            panel->addElement(b1, 4, 4);
            panel->addElement(b2, 4, 24);

            b1->startFocus();

            elements[0] = b1;
            elements[1] = b2;
            break;
        }
        case LUA_MENU:
            break;
        default:
            break;
    }
}

Menu::Menu(MenuClass mc, char const *lua, Renderer *r, SoundSystem *snd, GamePlayState* gps) {
    if (mc == LUA_MENU) {
        for (int i = 0; i < 16; i++) {
            elements[i] = nullptr;
        }

        renderer = r;
        soundSystem = snd;
        this->gps = gps;

        clink = snd->loadSFX("hover.wav");
        chime = snd->loadSFX("select.wav");
        fontAtlas = r->loadTexture("fontatlas.png");
        panel = new Panel(r, 300, 200);
    } else {
        Menu(mc, r, snd, gps);
    }
}

Menu::~Menu() {
    panel->destroy();
    delete panel;
}

void Menu::Render() {
    panel->Render();
}

void Menu::OnButtonStart() {
    soundSystem->playSFX(chime);
    gps->RequestSwitchState(WORLD);
}

void Menu::OnButtonA() {
    Button* selB = dynamic_cast<Button*>(panel->focusedElement());

    if (selB != nullptr)
    {
        if (selB->GetTag() == "resume")
        {
            soundSystem->playSFX(chime);
            gps->RequestSwitchState(WORLD);
        }
        else if (selB->GetTag() == "quit")
        {
            soundSystem->playSFX(chime);
            gps->RequestSwitchState(EXIT);
        }
    }
}

void Menu::OnButtonB() {
    OnButtonStart();
}

void Menu::OnButtonUp() {
    if (panel->focusedElement() != nullptr) {
        if (panel->focusedElement()->giveFocusUp())
            soundSystem->playSFX(clink);
    }
}

void Menu::OnButtonDown() {
    if (panel->focusedElement() != nullptr) {
        if (panel->focusedElement()->giveFocusDown())
            soundSystem->playSFX(clink);
    }
}

void Menu::OnButtonLeft() {

}

void Menu::OnButtonRight() {

}

