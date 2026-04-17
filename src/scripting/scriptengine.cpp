#include "scriptengine.h"
#include <platform/platform.h>
#include <algorithm>

ScriptEngine::ScriptEngine(GamePlayState *gps, TileMap *tm) {
    this->gps = gps;
    this->tm = tm;
    m_lua = luaL_newstate();
    luaL_openlibs(m_lua);
    LuminaLibrary::registerLuminaLibrary(m_lua);
}

ScriptEngine::~ScriptEngine() {
    if (m_lua) lua_close(m_lua);
}

bool ScriptEngine::runScript(const char* script, const char* function) {
    library.setGamePlayState(gps);
    library.setTileMap(tm);

    lua_pushcfunction(m_lua, &errorHandler);
    int msgh = lua_gettop(m_lua);
    if (luaL_loadfile(m_lua, LuminaUtils::osPath(script).c_str()) != LUA_OK) {
        library.MessageBox("Lua Load Error");
        lua_pop(m_lua, 2);
        return false;
    }

    lua_pushlightuserdata(m_lua, &library);
    lua_setfield(m_lua, LUA_REGISTRYINDEX, "LuminaLibrary");

    if (lua_pcall(m_lua, 0, 0, msgh) != LUA_OK) {
        library.MessageBox("Lua Run Error");
#ifdef PLATFORM_PC
        printf("Lua initial pcall error. Stack Size: %d\n", lua_gettop(m_lua));
#endif
        lua_pop(m_lua, 2);
        return false;
    }

    lua_State* sur = lua_newthread(m_lua);
    lua_pushvalue(m_lua, -1);
    int ref = luaL_ref(m_lua, LUA_REGISTRYINDEX);
    lua_pop(m_lua, 1);

    lua_getglobal(sur, function);
    if (lua_type(sur, -1) != LUA_TFUNCTION) {
        luaL_unref(m_lua, LUA_REGISTRYINDEX, ref);
        return false;
    }

    int nresults = 0;
    int status = lua_resume(sur, m_lua, 0, &nresults);

    if (status == LUA_OK) {
        lua_pop(sur, nresults);
        luaL_unref(m_lua, LUA_REGISTRYINDEX, ref);
        return true;
    } else if (status == LUA_YIELD) {
        ScriptSubroutine s;
        s.m_cr = sur;
        //s.ref = ref;
        s.name = function;
        s.isAlive = (status != LUA_OK);

        const char* tag = lua_tostring(sur, -2);
        if (strcmp(tag, "wait") == 0) {
            s.waittimer = (float)lua_tonumber(sur, -1);
            //printf("Lua wait timer: %f\n", s.waittimer);
        }
        lua_pop(sur, nresults);
        subroutines.push_back(s);
    } else if (status != LUA_OK) {
#ifdef PLATFORM_PC
        printf("Lua error: %s\n", lua_tostring(sur, 1));
#endif
        luaL_unref(m_lua, LUA_REGISTRYINDEX, ref);
        return false;
    }
    return true;
}

void ScriptEngine::updateScripts() {
    for (auto& cr : subroutines) {
        if (!cr.isAlive) continue;

        if (cr.waittimer > 0.0f) {
            cr.waittimer -= (1.0f / static_cast<float>(FRAME_RATE));
            if (cr.waittimer > 0.0f) continue;
        }

        int nresults = 0;
        int status = lua_resume(cr.m_cr, m_lua, 0, &nresults);

        if (status == LUA_YIELD) {
            const char* tag = lua_tostring(cr.m_cr, -2);

            if (strcmp(tag, "wait") == 0) {
                cr.waittimer = (float)lua_tonumber(cr.m_cr, -1);
                //printf("Lua wait timer: %f\n", cr.waittimer);
            }

            lua_pop(cr.m_cr, nresults);
        } else if (status == LUA_OK) {
            cr.isAlive = false;
        } else {
            const char* error = lua_tostring(cr.m_cr, 1);
            //printf("Lua error: %s\n", error);
            library.MessageBox("Lua Runtime Error");
            cr.isAlive = false;
        }
    }

    subroutines.erase(
        std::remove_if(subroutines.begin(), subroutines.end(),
        [](const ScriptSubroutine& sub) {
            if (!sub.isAlive) printf("[Script] erasing %s\n", sub.name.c_str());
            return !sub.isAlive;
        }),
        subroutines.end()
        );
}

int ScriptEngine::errorHandler(lua_State* m_lua) {
    const char* error = lua_tostring(m_lua, -1);
#ifdef PLATFORM_PC
    printf("Lua error: %s\n", error);
#endif
    luaL_traceback(m_lua, m_lua, error, 1);
    return 1;
}
