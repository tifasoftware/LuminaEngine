#pragma once
#include "text.h"
#include "panel.h"

class Dialogue {
    public:
    Dialogue(Renderer* r);
    ~Dialogue();
    void SetFont(int font) { text->SetFont(font); underScore->SetFont(font); }
    void DisplayDialogue(const char* text);
    void advance();
    bool isComplete() {return completed;}
    bool isEngaged() {return engaged;}
    void draw();

    private:
    Renderer* renderer;
    Panel* panel;
    Text* text;
    Text* underScore;
    char dialogueText[128];
    char displayText[128];
    int displayTextLength;
    bool completed;
    bool engaged;
    int frame;
};