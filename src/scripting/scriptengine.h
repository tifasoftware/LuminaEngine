#pragma once

#include "luminalibrary.h"
#include "entities/TileMap.h"
#include "game/gameplay_state.h"
#include "common/utils.h"

extern "C" {
    #include "lua.h"
    #include "lualib.h"
    #include "lauxlib.h"
    }

#include <string>
#include <functional>
#include <vector>

struct ScriptSubroutine {
    lua_State* m_cr;
    std::string name;
    float waittimer = 0.0f;
    bool isAlive = true;
    bool pause = false;
    bool firstFrame = true;
};

class ScriptEngine {
    public:
    ScriptEngine(GamePlayState* gps, TileMap* tm);
    ~ScriptEngine();

    bool runScript(const char* script, const char* function);
    void updateScripts(bool unpause);

    private:
    lua_State* m_lua;
    static int errorHandler(lua_State* m_lua);

    GamePlayState* gps = nullptr;
    TileMap* tm = nullptr;

    LuminaLibrary library = LuminaLibrary();
    std::vector<ScriptSubroutine> subroutines;
};