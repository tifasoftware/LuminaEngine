#pragma once

#include <lumina.h>

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

    bool gameRunning();
    void Exit();

    void GameLoop();

    private:
    const int FRAME_RATE = 60;
    const int REDRAW_DELAY = 1000 / FRAME_RATE;

    Character* lumina;
    TileMap* tm;
    Renderer* r;
    SoundSystem* snd;
    Fade* f;
    Panel* panel;

    SDL_Window* window;
    SDL_Event event;

    GameState gameState = WORLD;
    GameState newGameState = WORLD;
    bool wantNewState = false;
    bool inTransition = true;

    int clink = -1;
    int chime = -1;
    int fontAtlas = -1;

    int luminaX;
    int luminaY;

    int luminaMoveX = 0;
    int luminaMoveY = 0;

    int luminaMoveRate = 2;
};