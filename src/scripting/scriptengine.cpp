#include "scriptengine.h"

ScriptEngine::ScriptEngine(Dialogue *d, GamePlayState *gps, TileMap *tm) {
    this->dialogue = d;
    this->gps = gps;
    this->tm = tm;
    m_lua = luaL_newstate();
    luaL_openlibs(m_lua);
}

ScriptEngine::~ScriptEngine() {
    if (m_lua) lua_close(m_lua);
}

bool ScriptEngine::runScript(const char* script) {
    lua_pushcfunction(m_lua, &errorHandler);
    int msgh = lua_gettop(m_lua);
    if (luaL_loadfile(m_lua, LuminaUtils::osPath(script).c_str()) != LUA_OK) {
        dialogue->DisplayDialogue("Lua Load Error");
        lua_pop(m_lua, 2);
        return false;
    }
    if (lua_pcall(m_lua, msgh, 0, 0) != LUA_OK) {
        dialogue->DisplayDialogue("Lua Run Error");
        lua_pop(m_lua, 2);
        return false;
    }
    lua_pop(m_lua, 1);
    return true;
}

int ScriptEngine::errorHandler(lua_State* m_lua) {
    const char* error = lua_tostring(m_lua, -1);
    luaL_traceback(m_lua, m_lua, error, 1);
    return 1;
}
