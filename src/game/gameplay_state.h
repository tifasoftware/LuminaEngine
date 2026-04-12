#pragma once
#include "common/types.h"

class GamePlayState {
    public:
    int characterX = 0;
    int characterY = 0;
    int screenX = 0;
    int screenY = 0;

    void moveCharacter(int x, int y) { characterX += x; characterY += y; }
    void moveScreen(int x, int y) { screenX += x; screenY += y; }

    void RequestSwitchState(GameState newState);
    void RequestMapChange(const char* newMapName);
    void RequestRunScript(const char* scriptName);

    int LoadFromFile(const char* file);
    int SaveToFile(const char* file);

    GameState gameState = WORLD;
    GameState newGameState = WORLD;
    bool wantNewState = false;
    bool inTransition = true;
    bool wantCallScript = false;
    bool newMap = false;

    char mapName[64] = "scrolltest.lmap";
    char nextScript[64] = "";
    char lastMapName[64] = "start";
    char music[64] = "bgm0.ogg";

    bool introShown = false;
};
