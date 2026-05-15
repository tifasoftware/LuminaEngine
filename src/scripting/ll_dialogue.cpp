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

int LuminaLibrary::DisplayQuestion(Question* q)
{
    QuestionBox* qb = new QuestionBox(tm->getRenderer(), tm);
    gps->DispatchOverlay(qb);
    qb->DisplayQuestion(q);
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

int LuminaLibrary::l_DisplayQuestionFinished(lua_State *L, int status, lua_KContext ctx) {
    Question* q = reinterpret_cast<Question*>(ctx);
    lua_pushinteger(L, q->returnAnswer);

    delete q;
    return 1;
}

int LuminaLibrary::l_DisplayQuestion(lua_State *L) {
    std::string dialogueText = lua_tostring(L, 1);
    std::string characterName = lua_tostring(L, 2);
    int charIndex = lua_tonumber(L, 3);
    std::string a1 = lua_tostring(L, 4);
    std::string a2 = "";
    std::string a3 = "";
    std::string a4 = "";
    int answers = 1;

    int argc = lua_gettop(L);

    if (argc >= 5) {
        a2 = lua_tostring(L, 5);
        answers++;
    }
    if (argc >= 6) {
        a3 = lua_tostring(L, 6);
        answers++;
    }
    if (argc >= 7) {
        a4 = lua_tostring(L, 7);
        answers++;
    }

    Question* q = new Question();
    q->questionText = dialogueText;
    q->charName = characterName;
    q->textureIndex = charIndex;
    q->answer1 = a1;
    q->answer2 = a2;
    q->answer3 = a3;
    q->answer4 = a4;
    q->totalAnswers = answers;

    getLuaInstance(L)->DisplayQuestion(q);

    lua_pushstring(L, "pause");
    lua_pushnumber(L, 0.0f);
    return lua_yieldk(L, 2, reinterpret_cast<lua_KContext>(q), l_DisplayQuestionFinished);
}