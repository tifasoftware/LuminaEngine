#pragma once
#include "../imagebox.h"
#include "overlay.h"
#include "../rich_text.h"
#include "../panel.h"
#include "game/IControllable.h"

class Dialogue : public Overlay {
    public:
    Dialogue(Renderer* r, IControllable* p);
    ~Dialogue() override;

    void SetFont(int font) override { text->SetFont(font); characterName->SetFont(font); underScore->SetFont(font); }
    bool IsFontSet() override { return text->isFontSet(); }

    void DisplayDialogue(const char* text, const char* charName, int textureIndex);
    void advance();
    void draw() override;

    //IControllable
    void OnButtonA() override { advance(); }
    void OnButtonStart() override { completed=true; advance(); }
    void OnQuit() override { parent-> OnQuit(); }

    private:
    Panel* panel;
    RichText* text;
    RichText* characterName;
    RichText* underScore;

    ImageBox* imageBox;

    char dialogueText[128];
    char displayText[128];
    int displayTextLength;

    int frame;
};
