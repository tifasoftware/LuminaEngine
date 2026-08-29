#pragma once

#include <lumina.h>

#include "gameplay_state.h"
#include "controller.h"
#include "../vgui/overlays/dialogue.h"
#include "scripting/scriptengine.h"
#include "vgui/menu.h"

#if (defined(PLATFORM_PC) && defined(USER_LIGHTNING)) || defined(PLATFORM_ANDROID)
#include "vgui/mobile/os_controls.h"
#endif

class GamePlay
{
    public:
    GamePlay();

    void BlackDraw();

    void WorldDraw();
    void WorldStart();
    void WorldExit();

    void MenuDraw();
    void MenuStart();
    void MenuExit();

    void BattleDraw();
    void BattleStart();
    void BattleExit();

    void CinematicDraw();
    void CinematicStart();
    void CinematicExit();

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

#if (defined(PLATFORM_PC) && defined(USER_LIGHTNING)) || defined(PLATFORM_ANDROID)
    OnScreenControls* osc;
#endif

    SDL_Window* window;
    SDL_Event event;

    ISecondaryActivity* menu;
};
