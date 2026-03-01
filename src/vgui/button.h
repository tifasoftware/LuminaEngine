#pragma once

#include <vgui/UIElement.h>
#include <vgui/text.h>

class Button : public UIElement 
{
    public:
    Button(const char* text, int fti);
    void render(Renderer* r) override;
    void destroy() override { return; };
    void move(int x, int y) override;

    private:
    char label[32];
    Text t_obj;
    
};