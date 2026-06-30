cmake_minimum_required(VERSION 3.11)

project(LuminaEngine)

set(LE32BIT ON CACHE BOOL "Build for 32-bit")
set(LUMINA_ROOT "../../../..")

if ((CMAKE_ANDROID_ARCH STREQUAL "arm64") OR (CMAKE_ANDROID_ARCH STREQUAL "x86_64"))
    set(LE32BIT OFF)
endif ()

file (GLOB_RECURSE SOURCES "${LUMINA_ROOT}/src/*.cpp")
file (GLOB LUA_SOURCES "${LUMINA_ROOT}/libs/lua-5.5.0/src/*.c")
file (GLOB LUA_ASSETS "${LUMINA_ROOT}/assets/*.lua")
file (GLOB PNG_ASSETS "${LUMINA_ROOT}/assets/*.png")
file (GLOB OGG_ASSETS "${LUMINA_ROOT}/assets/*.ogg")
file (GLOB WAV_ASSETS "${LUMINA_ROOT}/assets/*.wav")
file (GLOB LMAP_ASSETS "${LUMINA_ROOT}/assets/*.lmap")

add_library(${PROJECT_NAME} SHARED ${SOURCES})

add_library(lua SHARED ${LUA_SOURCES})

target_include_directories(lua PUBLIC
        ${LUMINA_ROOT}/external/lua/src
)

target_include_directories(${PROJECT_NAME} PRIVATE
        ${LUMINA_ROOT}/src
        ${LUMINA_ROOT}/libs/lua-5.5.0/src/
        ../include
)

target_compile_definitions(lua PRIVATE LUA_32BITS)

target_link_libraries(${PROJECT_NAME} lua SDL2 SDL2_image SDL2_mixer)