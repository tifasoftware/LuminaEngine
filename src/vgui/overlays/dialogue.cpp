#include "dialogue.h"

#include "entities/TileMap.h"

Dialogue::Dialogue(Renderer* r, IControllable* p) : Overlay(r, p) {
    text = new RichText();
    characterName = new Text();
    imageBox = new ImageBox();
    panel = new Panel(r, 3, r->GetHeight() - 103, r->GetWidth() - 6, 100);
    underScore = new Text();

    panel->addElement(characterName, 2, 2);
    panel->addElement(text, 68, 20);
    panel->addElement(imageBox, 2, 20);
    panel->addElement(underScore, panel->getW() - 20, panel->getH() - 20);

    displayTextLength = 0;

    frame = 0;
}

Dialogue::~Dialogue() {
    panel->destroy();
    delete panel;
    panel = nullptr;
    text = nullptr;
    characterName = nullptr;
    imageBox = nullptr;
    underScore = nullptr;
}

void Dialogue::DisplayDialogue(const char *t, const char *charName, int textureIndex) {
    characterName->SetText(charName);
    text->SetText(t);

    imageBox->setTexture(textureIndex);

    engaged = true;
    completed = false;
    displayTextLength = 0;
    frame = 0;
}

void Dialogue::advance() {
    if (!completed) {
        text->SetTrim(-1);
        underScore->SetText("-");
        completed = true;
    } else {
        engaged = false;
        isActive = false;
    }
}

void Dialogue::draw() {
    if (!completed) {
        if (frame % 2 == 0) {
            text->IncrementTrim();
            displayTextLength++;
        }
        frame++;
        if (displayTextLength >= text->GetTextLength()) {
            completed = true;
            underScore->SetText("-");
        }
    } else {

    }
    panel->Render();
    //text->render(renderer);

    // if (completed) underScore->render(renderer);
}

