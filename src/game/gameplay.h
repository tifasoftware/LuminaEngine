#pragma once

#include <lumina.h>

#include "gameplay_state.h"
#include "controller.h"
#include "vgui/dialogue.h"

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
    void RequestSwitchState(GameState newState);
    void RequestMapChange(const char* newMapName);
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
    Fade* f;
    Panel* panel;
    Dialogue* dialogue;

    SDL_Window* window;
    SDL_Event event;

    GameState gameState = WORLD;
    GameState newGameState = WORLD;
    bool wantNewState = false;
    bool inTransition = true;
    bool newMap = false;

    int clink = -1;
    int chime = -1;
    int fontAtlas = -1;

    int luminaMoveX = 0;
    int luminaMoveY = 0;

    int luminaMoveRate = 2;

    char mapName[64] = "scrolltest.lmap";
    char lastMapName[64] = "start";
    char music[64] = "bgm0.ogg";

    bool introShown = false;
};
