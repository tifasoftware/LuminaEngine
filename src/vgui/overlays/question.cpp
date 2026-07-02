#include "question.h"

QuestionBox::QuestionBox(Renderer* r, IControllable* p) : Overlay(r,p) {
    characterName = new Text();
    imageBox = new ImageBox();
    panel = new Panel(r, 3, r->GetHeight() - 103, r->GetWidth() - 6, 100);
    answer1 = new Button("a1");
    answer2 = new Button("a2");
    answer3 = new Button("a3");
    answer4 = new Button("a4");

    panel->addElement(characterName, 2, 2);
    panel->addElement(imageBox, 2, 20);
    panel->addElement(answer1, 68, 20);
    panel->addElement(answer2, 68, 40);
    panel->addElement(answer3, 68, 60);
    panel->addElement(answer4, 68, 80);

    questionPanel = new Panel(renderer, 3, r->GetHeight() - 124, r->GetWidth() - 6, 20);
    questionText = new Text();

    questionPanel->addElement(questionText, 2, 2);
}

QuestionBox::~QuestionBox() {
    panel->destroy();
    questionPanel->destroy();
    delete panel;
    delete questionPanel;
    panel = nullptr;
    questionPanel = nullptr;
    questionText = nullptr;
    characterName = nullptr;
    imageBox = nullptr;
    answer1 = nullptr;
    answer2 = nullptr;
    answer3 = nullptr;
    answer4 = nullptr;
}

void QuestionBox::DisplayQuestion(Question* q) {
    question = q;

    characterName->SetText(q->charName.c_str());
    questionText->SetText(q->questionText.c_str());
    imageBox->setTexture(q->textureIndex);

    answer1->SetText(q->answer1.c_str());
    if (q->totalAnswers >= 2) {
        answer2->SetText(q->answer2.c_str());
        answer1->addLowerElement(answer2);
        answer2->addUpperElement(answer1);
    } else {
        //Loopback
        answer2->addLowerElement(answer1);
        answer1->addUpperElement(answer2);
    }

    if (q->totalAnswers >= 3) {
        answer3->SetText(q->answer3.c_str());
        answer2->addLowerElement(answer3);
        answer3->addUpperElement(answer2);
    } else {
        //Loopback
        answer3->addLowerElement(answer1);
        answer1->addUpperElement(answer3);
    }

    if (q->totalAnswers == 4) {
        answer4->SetText(q->answer4.c_str());
        answer3->addLowerElement(answer4);
        answer4->addUpperElement(answer3);

        //Loopback
        answer4->addLowerElement(answer1);
        answer1->addUpperElement(answer4);
    }

    answer1->startFocus();

    engaged = true;
    completed = false;
}

void QuestionBox::draw() {
    panel->Render();
    questionPanel->Render();
}

void QuestionBox::OnButtonA() {
    Button* selB = dynamic_cast<Button*>(panel->focusedElement());

    if (selB != nullptr) {
        if (selB->GetTag() == "a1") question->returnAnswer = 1;
        else if (selB->GetTag() == "a2") question->returnAnswer = 2;
        else if (selB->GetTag() == "a3") question->returnAnswer = 3;
        else if (selB->GetTag() == "a4") question->returnAnswer = 4;
    }

    engaged = false;
    isActive = false;
}

void QuestionBox::OnButtonUp() {
    if (panel->focusedElement() != nullptr) {
        panel->focusedElement()->giveFocusUp();
            //soundSystem->playSFX(clink);
    }
}

void QuestionBox::OnButtonDown() {
    if (panel->focusedElement() != nullptr) {
        panel->focusedElement()->giveFocusDown();
            //soundSystem->playSFX(clink);
    }
}
