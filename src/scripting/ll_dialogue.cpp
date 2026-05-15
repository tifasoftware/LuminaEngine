#include "lumina.h"
#include "luminalibrary.h"

#include "vgui/messagebox.h"

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