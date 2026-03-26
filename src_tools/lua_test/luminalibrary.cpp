#include "luminalibrary.h"

#include <iostream>
#include <ostream>

LuminaLibrary::LuminaLibrary() {

}

LuminaLibrary::~LuminaLibrary() {

}

void LuminaLibrary::printToScreen(std::string text) {
    std::cout << text << std::endl;
}

LuminaLibrary *LuminaLibrary::getLuminaLibrary(lua_State *L) {
    lua_getfield(L, LUA_REGISTRYINDEX, "LuminaLibrary");
    LuminaLibrary* em = static_cast<LuminaLibrary*>(lua_touserdata(L, -1));
    lua_pop(L, 1);
    return em;
}

int LuminaLibrary::l_printToScreen(lua_State *L) {
    std::string text = lua_tostring(L, 1);
    getLuminaLibrary(L)->printToScreen(text);
    return 0;
}

int LuminaLibrary::l_getFactorA(lua_State *L) {
    lua_pushinteger(L, getLuminaLibrary(L)->getFactorA());
    return 1;
}

int LuminaLibrary::l_getFactorB(lua_State *L) {
    lua_pushinteger(L, getLuminaLibrary(L)->getFactorB());
    return 1;
}

int LuminaLibrary::l_addFactors(lua_State *L) {
    int a = lua_tointeger(L, 1);
    int b = lua_tointeger(L, 2);
    lua_pushinteger(L, getLuminaLibrary(L)->addFactors(a, b));
    return 1;
}

void LuminaLibrary::registerLuminaLibrary(lua_State *L) {
    static const luaL_Reg funcs[] = {
        {"print", l_printToScreen},
        {"getFactorA", l_getFactorA},
        {"getFactorB", l_getFactorB},
        {"addFactors", l_addFactors},
        {nullptr, nullptr}
    };
    luaL_newlib(L, funcs);
    lua_setglobal(L, "lumina");
}
