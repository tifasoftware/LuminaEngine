#include "gameplay_state.h"
#include <cstring>

#include "common/types.h"

void GamePlayState::RequestMapChange(const char *newMapName) {
    wantNewState = true;
    newMap = true;
    strncpy(lastMapName, mapName, sizeof(lastMapName) - 1);  // copy current into last
    strncpy(mapName, newMapName, sizeof(mapName) - 1);
}

void GamePlayState::RequestSwitchState(GameState newState)
{
    newGameState = newState;
    wantNewState = true;
}
