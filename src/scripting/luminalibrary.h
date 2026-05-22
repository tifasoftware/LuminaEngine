#pragma once
#include <string>

#include "../vgui/overlays/dialogue.h"
#include "entities/TileMap.h"
#include "game/gameplay_state.h"
#include "../vgui/overlays/question.h"

extern "C" {
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
}

class LuminaLibrary {
    public:
    LuminaLibrary();
    ~LuminaLibrary();

    void DisplayMessageBox(std::string message);
    void DisplayDialogue(std::string dialogueText, std::string characterName, int characterProfile);
    void DisplayQuestion(Question* q);

    int LoadTexture(std::string textureFile);
    void ReplaceTexture(std::string textureFile, int index);
    void UnloadTexture(int index);

    //Lumina Engine Connections
    void setGamePlayState(GamePlayState* g) { this->gps = g; }
    void setTileMap(TileMap* t) { this->tm = t; }

    //Lua Connections
    static LuminaLibrary* getLuaInstance(lua_State* L);
    static void registerLuminaLibrary(lua_State* L);

    //Lua Bindings
    static int l_DisplayMessageBox(lua_State *L);
    static int l_DisplayDialogue(lua_State *L);
    static int l_DisplayQuestion(lua_State *L);
    static int l_DisplayQuestionFinished(lua_State *L, int status, lua_KContext ctx);

    static int l_wait(lua_State *L);
    static int l_drawFrame(lua_State *L);

    static int l_loadTexture(lua_State *L);
    static int l_replaceTexture(lua_State *L);
    static int l_unloadTexture(lua_State *L);

private:
    GamePlayState* gps;
    TileMap* tm;
};