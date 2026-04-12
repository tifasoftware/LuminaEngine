#include "gameplay_state.h"

#include <cstdlib>
#include <cstring>

#include "common/types.h"
#include "formats/lsav.h"

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

int GamePlayState::LoadFromFile(const char *file) {
    LSAVLoader loader = LSAVLoader(file);
    LSAVHeader* lsav = loader.load();

    if (!lsav) return -1;
    if (strncmp(lsav->magic, "LSAV", 4) != 0) return -1;
    if (strncmp(lsav->gameID, LUMINA_ENGINE_DEMO_ID, 255) != 0) return -1;

    this->characterX = lsav->charX;
    this->characterY = lsav->charY;
    this->screenX = lsav->scrnX;
    this->screenY = lsav->scrnY;

    strncpy(mapName, lsav->currMap, 63);
    strncpy(music, lsav->music, 63);

    newMap = false;
    newGameState = WORLD;
    introShown = true;
    wantNewState = true;

    delete lsav;

    return 0;
}

int GamePlayState::SaveToFile(const char *file) {
    LSAVWriter writer = LSAVWriter(file);
    LSAVHeader* lsav = (LSAVHeader*)malloc(sizeof(LSAVHeader));

    if (!lsav) {
        return -1;
    }

    strncpy(lsav->magic, "LSAV", 4);
    strncpy(lsav->gameID, LUMINA_ENGINE_DEMO_ID, 255);

    lsav->charX = this->characterX;
    lsav->charY = this->characterY;
    lsav->scrnX = this->screenX;
    lsav->scrnY = this->screenY;

    strncpy(lsav->currMap, mapName, 63);
    strncpy(lsav->music, music, 63);

    writer.write(lsav);
    free(lsav);
    return 0;
}
