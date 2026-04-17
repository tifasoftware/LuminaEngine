#pragma once
#include "overlay.h"
#include "text.h"
#include "panel.h"
#include "game/IControllable.h"

class Dialogue : public Overlay {
    public:
    Dialogue(Renderer* r, IControllable* p);
    ~Dialogue() override;

    void SetFont(int font) override { text->SetFont(font); underScore->SetFont(font); }
    bool IsFontSet() override { return text->isFontSet(); }

    void DisplayDialogue(const char* text);
    void advance();
    void draw() override;

    //IControllable
    void OnButtonA() override { advance(); }
    void OnButtonStart() override { completed=true; advance(); }
    void OnQuit() override { parent-> OnQuit(); }

    private:
    Panel* panel;
    Text* text;
    Text* underScore;
    char dialogueText[128];
    char displayText[128];
    int displayTextLength;

    int frame;
};
