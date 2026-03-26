#pragma once
#include <string>

extern "C" {
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}

class LuminaLibrary {
    public:
    LuminaLibrary();
    ~LuminaLibrary();

    void printToScreen(std::string text);

    int getFactorA() { return 9; }
    int getFactorB() { return 10; }

    int addFactors(int a, int b) { return a + b; }

    static LuminaLibrary* getLuminaLibrary(lua_State* L);
    static void registerLuminaLibrary(lua_State* L);

    static int l_printToScreen(lua_State* L);
    static int l_getFactorA(lua_State* L);
    static int l_getFactorB(lua_State* L);
    static int l_addFactors(lua_State* L);

    //static const luaL_Reg luminaLibrary_llib[];

};