#pragma once
#include "common/types.h"
#include "game/gameplay_state.h"
#include "game/IControllable.h"

#include "graphics/Renderer.h"
#include "sound/soundsystem.h"
#include "vgui/button.h"
#include "vgui/panel.h"

class Menu : public IControllable {
    public:
    Menu(MenuClass mc, Renderer* r, SoundSystem* snd, GamePlayState* gps);
    Menu(MenuClass mc, char const* lua, Renderer* r, SoundSystem* snd, GamePlayState* gps);
    ~Menu();

    void Render();

    //IControllable
    void OnButtonA() override;
    void OnButtonB() override;
    void OnButtonStart() override;

    void OnQuit() override { gps->RequestSwitchState(EXIT); }

    void OnButtonUp() override;
    void OnButtonDown() override;
    void OnButtonLeft() override;
    void OnButtonRight() override;

private:
    MenuClass previousMenu = NO_MENU;
    char luafile[128] = "";

    int fontAtlas = -1;
    int clink = -1;
    int chime = -1;
    Panel* panel;

    Renderer* renderer;
    SoundSystem* soundSystem;
    UIElement* elements[16];
    GamePlayState* gps;
};
