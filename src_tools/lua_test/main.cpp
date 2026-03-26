#include <iostream>
#include <ostream>

#include "luminalibrary.h"

extern "C" {
    #include <lua.h>
    #include <lauxlib.h>
    #include <lualib.h>
}

#include <string>
#include <functional>

// Incase the lua file is bad
int errorHandle(lua_State* L) {
    const char* msg = lua_tostring(L, -1);
    luaL_traceback(L, L, msg, 1);
    return 1;
}

int main(int argc, char *argv[]) {
    std::cout << "Calculating in Lua!" << std::endl;

// Create an instance of the Lua procesor
    lua_State* m_lua;
    m_lua = luaL_newstate();
    //Open the core utilities
    LuminaLibrary::registerLuminaLibrary(m_lua);

    //File loading routine
    std::cout << "Loading File" << std::endl;

    const char* file = "./test.lua";

    //Add an error handler to the stack first
    lua_pushcfunction(m_lua, &errorHandle);

    //Obtain the error handler's index
    int msgh;
    msgh = lua_gettop(m_lua);

    //Attempt to load the file
    if (luaL_loadfile(m_lua, file) != LUA_OK) {
        std::cerr << "Error loading test.lua" << std::endl;

        //push out error handler and the recieved error code in the stack
        lua_pop(m_lua, 2);
        return -1;
    }

    //Attempt to interpret the lua file
    if (lua_pcall(m_lua, 0, 0, msgh) != LUA_OK) {  // fixed: nargs=0, msgh last
        std::cerr << "Error running test.lua: "
                  << lua_tostring(m_lua, -1) << std::endl;

        //push out the error handler and the recieved error code in the stack
        lua_pop(m_lua, 2);
        return -1;
    }
    //push out the error handler
    lua_pop(m_lua, 1);

    std::cout << "File Loaded!" << std::endl;

    //Reinsert the error handler and get it's id
    lua_pushcfunction(m_lua, &errorHandle);
    msgh = lua_gettop(m_lua);

    LuminaLibrary* lib = new LuminaLibrary();
    lua_pushlightuserdata(m_lua, lib);
    lua_setfield(m_lua, LUA_REGISTRYINDEX, "LuminaLibrary");

    //Push the function name to the stack
    lua_getglobal(m_lua, "oncall");
    printf("oncall type: %s\n", lua_typename(m_lua, lua_type(m_lua, -1)));

    //Attempt to call the "OnCall" function
    if (lua_pcall(m_lua, 0, 0, msgh) != LUA_OK) {  // fixed: msgh last
        std::cerr << "Error calling oncall: "
                  << lua_tostring(m_lua, -1) << std::endl;

        //Pop out the Error handler and error message from the stack
        lua_pop(m_lua, 2);
        return -1;
    }

    printf("stack size: %d\n", lua_gettop(m_lua));

    //Pop out the result and the error handler from the stack
    lua_pop(m_lua, 1);

    delete lib;

    //Close the lua session
    if (m_lua) lua_close(m_lua);
}