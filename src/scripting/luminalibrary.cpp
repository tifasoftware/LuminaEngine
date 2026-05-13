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

void LuminaLibrary::DisplayMessageBox(std::string message) {
    MessageBox* mb = new MessageBox(tm->getRenderer(), tm);
    gps->DispatchOverlay(mb);
    mb->DisplayDialogue(message.c_str());
}

void LuminaLibrary::DisplayDialogue(std::string dialogueText, std::string characterName, int characterProfile) {
    Dialogue* dialogue = new Dialogue(tm->getRenderer(), tm);
    gps->DispatchOverlay(dialogue);
    dialogue->DisplayDialogue(dialogueText.c_str(), characterName.c_str(), characterProfile);
}

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

int LuminaLibrary::l_DisplayMessageBox(lua_State *L) {
    std::string message = lua_tostring(L, 1);
    getLuaInstance(L)->DisplayMessageBox(message);

    printf(message.c_str());

    lua_pushstring(L, "pause");
    lua_pushnumber(L, 0.0f);
    return lua_yield(L, 2);
}

int LuminaLibrary::l_DisplayDialogue(lua_State *L) {
    std::string message = lua_tostring(L, 1);
    std::string charName = lua_tostring(L, 2);
    int charIndex = lua_tonumber(L, 3);

    getLuaInstance(L)->DisplayDialogue(message, charName, charIndex);

    lua_pushstring(L, "pause");
    lua_pushnumber(L, 0.0f);
    return lua_yield(L, 2);
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
