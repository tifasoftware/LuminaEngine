#include "lumina.h"
#include "luminalibrary.h"

#include "../vgui/overlays/messagebox.h"

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

void LuminaLibrary::DisplayQuestion(Question* q)
{
    QuestionBox* qb = new QuestionBox(tm->getRenderer(), tm);
    gps->DispatchOverlay(qb);
    qb->DisplayQuestion(q);
}

int LuminaLibrary::l_DisplayMessageBox(lua_State *L) {
    std::string message = lua_tostring(L, 1);
    getLuaInstance(L)->DisplayMessageBox(message);

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

int LuminaLibrary::l_DisplayQuestionFinished(lua_State *L, int status, lua_KContext ctx) {
    Question* q = reinterpret_cast<Question*>(ctx);
    lua_pushinteger(L, q->returnAnswer);

    delete q;
    return 1;
}

int LuminaLibrary::l_DisplayQuestion(lua_State *L) {
    Question* q = new Question();
    q->questionText = lua_tostring(L, 1);
    q->charName = lua_tostring(L, 2);
    q->textureIndex = lua_tonumber(L, 3);
    q->answer1 = lua_tostring(L, 4);
    q->answer2 = "";
    q->answer3 = "";
    q->answer4 = "";
    q->totalAnswers = 1;

    int argc = lua_gettop(L);

    if (argc >= 5) {
        q->answer2 = lua_tostring(L, 5);
        q->totalAnswers++;
    }
    if (argc >= 6) {
        q->answer3 = lua_tostring(L, 6);
        q->totalAnswers++;
    }
    if (argc >= 7) {
        q->answer4 = lua_tostring(L, 7);
        q->totalAnswers++;
    }

    getLuaInstance(L)->DisplayQuestion(q);

    lua_pushstring(L, "pause");
    lua_pushnumber(L, 0.0f);
    return lua_yieldk(L, 2, reinterpret_cast<lua_KContext>(q), l_DisplayQuestionFinished);
}