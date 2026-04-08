#include "gameplay_state.h"
#include <cstring>

#include "common/types.h"

void GamePlayState::RequestMapChange(const char *newMapName) {
    wantNewState = true;
    newMap = true;
    strncpy(lastMapName, mapName, 63);  // copy current into last
    strncpy(mapName, newMapName, 63);
}

void GamePlayState::RequestSwitchState(GameState newState)
{
    newGameState = newState;
    wantNewState = true;
}

void GamePlayState::RequestRunScript(const char *scriptName) {
    strncpy(nextScript, scriptName, 63);
    wantCallScript = true;
}
