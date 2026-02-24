#pragma once

#include <graphics/Renderer.h>

class Fade
{
    public:
    Fade(Renderer* r);
    void FadeIn(float time);
    void FadeOut(float time);
    void Render(float deltaTime);
    bool isFading();

    private:
    int alpha;
    float totalTime;
    float currentTime;
    bool isFadingIn;
    bool isActive = false;
    Renderer* render;
};