#pragma once
#include "text.h"
#include "panel.h"
#include "game/IControllable.h"

class Dialogue : public IControllable {
    public:
    Dialogue(Renderer* r, IControllable* p);
    ~Dialogue();
    void SetFont(int font) { text->SetFont(font); underScore->SetFont(font); }
    void DisplayDialogue(const char* text);
    void advance();
    bool isComplete() {return completed;}
    bool isEngaged() {return engaged;}
    void draw();

    //IControllable
    void OnButtonA() override { advance(); }
    void OnButtonStart() override { completed=true; advance(); }
    void OnQuit() override { parent-> OnQuit(); }

    private:
    Renderer* renderer;
    Panel* panel;
    Text* text;
    Text* underScore;
    IControllable* parent;
    char dialogueText[128];
    char displayText[128];
    int displayTextLength;
    bool completed;
    bool engaged;
    int frame;
};
