#include "scriptengine.h"
#include <platform/platform.h>

ScriptEngine::ScriptEngine(Dialogue *d, GamePlayState *gps, TileMap *tm) {
    this->dialogue = d;
    this->gps = gps;
    this->tm = tm;
    m_lua = luaL_newstate();
    luaL_openlibs(m_lua);
    LuminaLibrary::registerLuminaLibrary(m_lua);
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

    LuminaLibrary* lib = new LuminaLibrary();
    lib->setDialogue(dialogue);
    lua_pushlightuserdata(m_lua, lib);
    lua_setfield(m_lua, LUA_REGISTRYINDEX, "LuminaLibrary");

    if (lua_pcall(m_lua, 0, 0, msgh) != LUA_OK) {
        dialogue->DisplayDialogue("Lua Run Error");
#ifdef PLATFORM_PC
        printf("Lua initial pcall error. Stack Size: %d\n", lua_gettop(m_lua));
#endif
        lua_pop(m_lua, 2);
        delete lib;
        return false;
    }

    lua_getglobal(m_lua, "onCall");
    if ((lua_isfunction(m_lua, -1))) {
        if (lua_pcall(m_lua, 0, 0, msgh) != LUA_OK) {
#ifdef PLATFORM_PC
            printf("Lua function pcall error. Stack Size: %d\n", lua_gettop(m_lua));
#endif
            dialogue->DisplayDialogue("Lua Run Error");
            lua_pop(m_lua, 2);
            delete lib;
            return false;
        }
    } else {
        dialogue->DisplayDialogue("Lua Run Error");
#ifdef PLATFORM_PC
        printf("Lua isfunction error. Stack Size: %d\n", lua_gettop(m_lua));
#endif
        lua_pop(m_lua, 2);
        delete lib;
        return false;
    }

    lua_remove(m_lua, msgh); // remove handler after success
    delete lib;
    return true;
}

int ScriptEngine::errorHandler(lua_State* m_lua) {
    const char* error = lua_tostring(m_lua, -1);
#ifdef PLATFORM_PC
    printf("Lua error: %s\n", error);
#endif
    luaL_traceback(m_lua, m_lua, error, 1);
    return 1;
}
