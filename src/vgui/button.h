#pragma once

#include <vgui/UIElement.h>
#include <vgui/text.h>

class Button : public UIElement 
{
    public:
    Button(const char* text, const char* tag, int fti);
    void render(Renderer* r) override;
    void destroy() override { return; };
    void move(int x, int y) override;

    bool giveFocusUp() override;
    bool giveFocusDown() override;
    void startFocus() override;

    const char* GetTag() { return tag; }

    //void select();
    void deSelect();

    //bool wasSelected() { return isSelected; }

    private:
    const char* tag;
    Text t_obj;

    //bool isSelected = false;
    
};