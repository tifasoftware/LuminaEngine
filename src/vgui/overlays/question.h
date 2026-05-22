#pragma once
#include <string>
#include "../button.h"
#include "../imagebox.h"
#include "overlay.h"
#include "../text.h"
#include "../panel.h"
#include "game/IControllable.h"

struct Question {
    std::string charName;
    std::string questionText;
    std::string answer1;
    std::string answer2;
    std::string answer3;
    std::string answer4;
    int totalAnswers;
    int textureIndex;

    int returnAnswer = -1;
};

class QuestionBox : public Overlay {
public:
    QuestionBox(Renderer* r, IControllable* p);
    ~QuestionBox() override;

    void SetFont(int font) override {
        questionText->SetFont(font);
        characterName->SetFont(font);
        answer1->SetFont(font);
        answer2->SetFont(font);
        answer3->SetFont(font);
        answer4->SetFont(font);
    }
    bool IsFontSet() override { return questionText->isFontSet(); }

    void DisplayQuestion(Question* q);
    void draw() override;

    //IControllable
    void OnButtonA() override;
    //void OnButtonLeft() override;
    //void OnButtonRight() override;
    void OnButtonUp() override;
    void OnButtonDown() override;
    void OnQuit() override { parent-> OnQuit(); }

private:
    Panel* panel;
    Text* characterName;

    Panel* questionPanel;
    Text* questionText;

    Button* answer1;
    Button* answer2;
    Button* answer3;
    Button* answer4;

    ImageBox* imageBox;

    //char questionText[128];
    //char answerText1[128];
    //int displayTextLength;

    int totalAnswers = 0;

    Question* question;
    //int frame;
};