add_executable(lua_test main.cpp)

file (GLOB LUA_FILES "${CMAKE_SOURCE_DIR}/src_tools/lua_test/*.lua")

set_target_properties(lua_test PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
)

target_include_directories(lua_test PRIVATE
        ${CMAKE_SOURCE_DIR}/libs/lua-5.5.0/src/
        ${CMAKE_SOURCE_DIR}/src
)
target_link_libraries(lua_test PRIVATE
        lua
)

add_custom_command(TARGET lua_test POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        ${LUA_FILES}
        ${CMAKE_BINARY_DIR}
)