#pragma once
#include "overlay.h"
#include <vgui/rich_text.h>
#include "../panel.h"
#include "game/IControllable.h"

class MessageBox : public Overlay {
    public:
    MessageBox(Renderer* r, IControllable* p);
    ~MessageBox() override;

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
    RichText* text;
    RichText* underScore;
    int displayTextLength;

    int frame;
};
