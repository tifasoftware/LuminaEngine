#pragma once

#include <lumina.h>

#include "gameplay_state.h"
#include "controller.h"
#include "../vgui/overlays/dialogue.h"
#include "scripting/scriptengine.h"
#include "vgui/menu.h"

#if defined(PLATFORM_PC) || defined(PLATFORM_ANDROID)
#include "vgui/mobile/os_controls.h"
#endif

class GamePlay
{
    public:
    GamePlay();
    void WorldDraw();
    void MenuDraw();
    void BattleDraw();

    void BlackDraw();

    void WorldStart();
    void MenuStart();
    void BattleStart();

    void WorldExit();
    void MenuExit();
    void BattleExit();

    void Splash();

    void SwitchState();
    void ChangeMusic(const char* newMusic);

    bool gameRunning();
    void Exit();

    void GameLoop();

    private:
    Controller* controller;
    GamePlayState gps;
    Character* lumina;
    TileMap* tm;
    Renderer* r;
    SoundSystem* snd;
    ScriptEngine* scriptEngine;
    Fade* f;

#if defined(PLATFORM_PC) || defined(PLATFORM_ANDROID)
    OnScreenControls* osc;
#endif

    SDL_Window* window;
    SDL_Event event;

    Menu* menu;

    int fontAtlas = -1;
};
