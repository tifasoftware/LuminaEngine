#include "gameplay.h"

void GamePlay::Splash() {
    int s = r->loadTexture("splash.png");

    int sx = (r->GetWidth() - 256) / 2;
    int sy = (r->GetHeight() - 256) / 2;

    f = new Fade(r);
    f->FadeIn(1.0f);

    while (f->isFading()){
        r->clear();
        r->drawSprite(s, sx, sy);
        f->Render(1.0f / FRAME_RATE);
        r->present();
        LuminaUtils::LuminaDelay(REDRAW_DELAY);
    }

    for (int i = 0; i < 180; i++) {
        r->clear();
        r->drawSprite(s, sx, sy);
        //f->Render(1.0f / FRAME_RATE);
        r->present();
        LuminaUtils::LuminaDelay(REDRAW_DELAY);
    }
    //LuminaUtils::LuminaDelay(3000);

    f->FadeOut(1.0f);

    while (f->isFading()){
        r->clear();
        r->drawSprite(s, sx, sy);
        f->Render(1.0f / FRAME_RATE);
        r->present();
        LuminaUtils::LuminaDelay(REDRAW_DELAY);
    }

    r->unloadAllTextures();

    r->clear();
    r->present();
}
