#include "dialogue.h"

#include "entities/TileMap.h"

Dialogue::Dialogue(Renderer* r, IControllable* p) : Overlay(r, p) {
    text = new Text();
    characterName = new Text();
    imageBox = new ImageBox();
    panel = new Panel(renderer, 3, SCREEN_H - 103, SCREEN_W - 6, 100);
    underScore = new Text();

    panel->addElement(characterName, 2, 2);
    panel->addElement(text, 68, 20);
    panel->addElement(imageBox, 2, 20);
    panel->addElement(underScore, panel->getW() - 20, panel->getH() - 20);

    strcpy(dialogueText, "");
    strcpy(displayText, "");
    displayTextLength = 0;

    frame = 0;
}

Dialogue::~Dialogue() {
    //delete text;
    //delete underScore;

    panel->destroy();
    delete panel;
    panel = nullptr;
    text = nullptr;
    characterName = nullptr;
    imageBox = nullptr;
    underScore = nullptr;
}

void Dialogue::DisplayDialogue(const char *text, const char *charName, int textureIndex) {
    strncpy(dialogueText, text, 127);
    strncpy(displayText, "", 127);

    characterName->SetText(charName);

    imageBox->setTexture(textureIndex);

    engaged = true;
    completed = false;
    displayTextLength = 0;
    frame = 0;
}

void Dialogue::advance() {
    if (!completed) {
        strncpy(displayText, dialogueText, 127);
        text->SetText(displayText);
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
            displayText[displayTextLength] = dialogueText[displayTextLength];
            displayTextLength++;
            text->SetText(displayText);

        }
        frame++;
        if (dialogueText[displayTextLength] == '\0') completed = true;
    } else {

    }
    panel->Render();
    text->render(renderer);

    if (completed) underScore->render(renderer);
}

