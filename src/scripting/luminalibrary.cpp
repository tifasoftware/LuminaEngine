#include "lumina.h"
#include "luminalibrary.h"

LuminaLibrary::LuminaLibrary() {
    dialogue = nullptr;
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
        {"MessageBox", l_MessageBox},
        {nullptr, nullptr}
    };
    luaL_newlib(L, funcs);
    lua_setglobal(L, "lumina");
}

void LuminaLibrary::MessageBox(std::string message) {
    if (dialogue != nullptr) {
        dialogue->DisplayDialogue(message.c_str());
    }
}

int LuminaLibrary::l_MessageBox(lua_State *L) {
    std::string message = lua_tostring(L, 1);
    getLuaInstance(L)->MessageBox(message);
    return 0;
}
