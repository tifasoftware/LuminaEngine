#include <iostream>
#include <ostream>

extern "C" {
    #include <lua.h>
    #include <lauxlib.h>
    #include <lualib.h>
}

#include <string>
#include <functional>

int errorHandle(lua_State* L) {
    const char* msg = lua_tostring(L, -1);
    luaL_traceback(L, L, msg, 1);
    return 1;
}

int main(int argc, char *argv[]) {
    std::cout << "Calculating in Lua!" << std::endl;

    lua_State* m_lua;
    m_lua = luaL_newstate();
    luaL_openlibs(m_lua);

    std::cout << "Loading File" << std::endl;

    const char* file = "./test.lua";

    lua_pushcfunction(m_lua, &errorHandle);
    int msgh;
    msgh = lua_gettop(m_lua);
    if (luaL_loadfile(m_lua, file) != LUA_OK) {
        std::cerr << "Error loading test.lua" << std::endl;
        lua_pop(m_lua, 2);
        return -1;
    }

    if (lua_pcall(m_lua, 0, 0, msgh) != LUA_OK) {  // fixed: nargs=0, msgh last
        std::cerr << "Error running test.lua: "
                  << lua_tostring(m_lua, -1) << std::endl;
        lua_pop(m_lua, 2);
        return -1;
    }
    lua_pop(m_lua, 1);

    std::cout << "File Loaded!" << std::endl;

    lua_pushcfunction(m_lua, &errorHandle);
    msgh = lua_gettop(m_lua);

    lua_getglobal(m_lua, "oncall");
    printf("oncall type: %s\n", lua_typename(m_lua, lua_type(m_lua, -1)));

    lua_pushinteger(m_lua, 9);
    lua_pushinteger(m_lua, 10);

    if (lua_pcall(m_lua, 2, 1, msgh) != LUA_OK) {  // fixed: msgh last
        std::cerr << "Error calling oncall: "
                  << lua_tostring(m_lua, -1) << std::endl;
        lua_pop(m_lua, 2);
        return -1;
    }

    int result = lua_tointeger(m_lua, -1);

    std::cout << result << std::endl;

    printf("stack size: %d\n", lua_gettop(m_lua));

    lua_pop(m_lua, 2);

    if (m_lua) lua_close(m_lua);
}