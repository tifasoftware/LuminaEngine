#include "lumina.h"
#include "luminalibrary.h"

int LuminaLibrary::LoadTexture(std::string textureFile) {
    if (tm != nullptr) {
        return tm->getRenderer()->loadTexture(textureFile.c_str());
    }
    return -1;
}

void LuminaLibrary::ReplaceTexture(std::string textureFile, int index) {
    if (tm != nullptr) {
        auto r = tm->getRenderer();
        r->unloadTexture(index);
        r->loadTexture(textureFile.c_str(), index);
    }
}

void LuminaLibrary::UnloadTexture(int index) {
    if (tm != nullptr) tm->getRenderer()->unloadTexture(index);
}

int LuminaLibrary::l_loadTexture(lua_State *L) {
    std::string textureFile = lua_tostring(L, 1);
    int index = getLuaInstance(L)->LoadTexture(textureFile);
    lua_pushinteger(L, index);
    return 1;
}

int LuminaLibrary::l_replaceTexture(lua_State *L) {
    std::string textureFile = lua_tostring(L, 1);
    int index = lua_tonumber(L, 2);
    getLuaInstance(L)->ReplaceTexture(textureFile, index);
    return 0;
}

int LuminaLibrary::l_unloadTexture(lua_State *L) {
    int index = lua_tonumber(L, 1);
    getLuaInstance(L)->UnloadTexture(index);
    return 0;
}