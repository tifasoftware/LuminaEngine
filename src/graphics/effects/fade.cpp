#include <graphics/Renderer.h>
#include <graphics/effects/fade.h>

Fade::Fade(Renderer* r)
{
    render = r;
}

void Fade::FadeIn(float time)
{
    totalTime = time;
    currentTime = 0;
    alpha = 255;
    isFadingIn = true;
    isActive = true;
#ifdef PLATFORM_3DS
    fadeAB = false;
#endif
}

void Fade::FadeOut(float time)
{
    totalTime = time;
    currentTime = 0;
    alpha = 0;
    isFadingIn = false;
    isActive = true;
#ifdef PLATFORM_3DS
    fadeAB = false;
#endif
}

bool Fade::isFading()
{
    return isActive;
}

void Fade::Render(float deltaTime)
{

    currentTime += deltaTime;

#ifdef PLATFORM_3DS
    if (fadeAB)
        render->floodOldOverlay();
    else
        render->floodOverlay(0,0,0, alpha);
#else
    render->floodOverlay(0,0,0, alpha);
#endif


    int deltaAlpha = 255 * (deltaTime / totalTime);
    if (isFadingIn)
    {
        alpha -= deltaAlpha;
    } else {
        alpha += deltaAlpha;
    }

    if (currentTime >= totalTime)
    {
        isActive = false;
    }

#ifdef PLATFORM_3DS
    fadeAB = (!fadeAB);
#endif
}
