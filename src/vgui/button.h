#pragma once

#include <vgui/UIElement.h>

class Button : public UIElement 
{
    public:
    Button(const char text);
    void render(Renderer* r) override;

    private:
    char label[32];
    
};