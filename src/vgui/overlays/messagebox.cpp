#include "messagebox.h"

#include "entities/TileMap.h"

MessageBox::MessageBox(Renderer* r, IControllable* p) : Overlay(r, p) {
    text = new RichText();
    panel = new Panel(renderer, 3, r->GetHeight() - 103, r->GetWidth() - 6, 100);
    underScore = new Text();

    panel->addElement(text, 2, 2);
    panel->addElement(underScore, panel->getW() - 20, panel->getH() - 20);

    displayTextLength = 0;

    frame = 0;
}

MessageBox::~MessageBox() {
    //delete text;
    //delete underScore;

    panel->destroy();
    delete panel;
    panel = nullptr;
    text = nullptr;
    underScore = nullptr;
}

void MessageBox::DisplayDialogue(const char *t) {
    text->SetText(t);
    engaged = true;
    completed = false;
    displayTextLength = 0;
    frame = 0;
}

void MessageBox::advance() {
    if (!completed) {
        underScore->SetText("-");
        completed = true;
    } else {
        engaged = false;
        isActive = false;
    }
}

void MessageBox::draw() {
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

