#pragma once

#include <lumina.h>

#include "gameplay_state.h"
#include "controller.h"
#include "vgui/dialogue.h"
#include "scripting/scriptengine.h"


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
    Panel* panel;
    Dialogue* dialogue;

    SDL_Window* window;
    SDL_Event event;

    int clink = -1;
    int chime = -1;
    int fontAtlas = -1;
};
