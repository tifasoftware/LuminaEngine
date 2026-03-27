#pragma once
#include <string>

#include "vgui/dialogue.h"

extern "C" {
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
}

class LuminaLibrary {
    public:
    LuminaLibrary();
    ~LuminaLibrary();

    void MessageBox(std::string message);

    //Lumina Engine Connections
    void setDialogue(Dialogue* d) { this->dialogue = d; }

    //Lua Connections
    static LuminaLibrary* getLuaInstance(lua_State* L);
    static void registerLuminaLibrary(lua_State* L);

    //Lua Bindings
    static int l_MessageBox(lua_State *L);
    static int l_wait(lua_State *L);
    static int l_drawFrame(lua_State *L);

private:
    Dialogue* dialogue;
};