#pragma once

#include <vgui/UIElement.h>
#include <vgui/text.h>

class Button : public UIElement 
{
    public:
    Button(const char* text, const char* tag, int fti);
    Button(const char* tag);
    void render(Renderer* r) override;
    void destroy() override { return; };
    void move(int x, int y) override;

    bool giveFocusUp() override;
    bool giveFocusDown() override;
    void startFocus() override;

    void SetText(const char* text) {t_obj.SetText(text);}
    void SetFont(int fti) {t_obj.SetFont(fti);}

    const char* GetTag() { return tag; }

    //void select();
    void deSelect();

    //bool wasSelected() { return isSelected; }

    private:
    const char* tag;
    Text t_obj;

    //bool isSelected = false;
    
};