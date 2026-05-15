#include "lumina.h"
#include "luminalibrary.h"

#include "vgui/messagebox.h"

LuminaLibrary::LuminaLibrary() {
    gps = nullptr;
    tm = nullptr;
}

LuminaLibrary::~LuminaLibrary() {

}

LuminaLibrary *LuminaLibrary::getLuaInstance(lua_State *L) {
    lua_getfield(L, LUA_REGISTRYINDEX, "LuminaLibrary");
    LuminaLibrary* em = static_cast<LuminaLibrary*>(lua_touserdata(L, -1));
    lua_pop(L, 1);
    return em;
}

void LuminaLibrary::registerLuminaLibrary(lua_State *L) {
    static const luaL_Reg funcs[] = {
        {"MessageBox", l_DisplayMessageBox},
        {"say", l_DisplayDialogue},
        {"wait", l_wait},
        {"drawFrame", l_drawFrame},
        {"loadTexture", l_loadTexture},
        {"replaceTexture", l_replaceTexture},
        {"unloadTexture", l_unloadTexture},
        {nullptr, nullptr}
    };
    luaL_newlib(L, funcs);
    lua_setglobal(L, "lumina");
}

int LuminaLibrary::l_wait(lua_State *L) {
    float seconds = (float)lua_tonumber(L, 1);
    lua_pushstring(L, "wait");
    lua_pushnumber(L, seconds);
    return lua_yield(L, 2);
}

int LuminaLibrary::l_drawFrame(lua_State *L) {
    float seconds = 1.0f / static_cast<float>(FRAME_RATE);
    lua_pushstring(L, "wait");
    lua_pushnumber(L, seconds);
    return lua_yield(L, 2);
}
