#pragma once

#include <lumina.h>

extern "C" {
    #include "lua.h"
    #include "lualib.h"
    #include "lauxlib.h"
    }

#include <string>
#include <functional>

class ScriptEngine {
    public:
    ScriptEngine(Dialogue* d, GamePlayState* gps, TileMap* tm);
    ~ScriptEngine();

    bool runScript(const char* script);

    private:
    lua_State* m_lua;
    static int errorHandler(lua_State* m_lua);

    Dialogue* dialogue = nullptr;
    GamePlayState* gps = nullptr;
    TileMap* tm = nullptr;
};