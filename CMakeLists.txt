cmake_minimum_required(VERSION 3.11)

project(LuminaEngine)

file (GLOB_RECURSE SOURCES "src/*.cpp")
file (GLOB PNG_ASSETS "assets/*.png")
file (GLOB OGG_ASSETS "assets/*.ogg")
file (GLOB LMAP_ASSETS "assets/*.lmap")

add_executable(${PROJECT_NAME} ${SOURCES})

include(FindPkgConfig)
pkg_search_module(SDL2 REQUIRED sdl2)
pkg_search_module(SDL2_IMAGE REQUIRED SDL2_image)
pkg_search_module(SDL2_MIXER REQUIRED SDL2_mixer)
#pkg_search_module(SDL2_TTF REQUIRED SDL2_ttf)
#pkg_search_module(LUA REQUIRED lua5.4)

target_include_directories(${PROJECT_NAME} PRIVATE
    ${SDL2_INCLUDE_DIRS}
    ${SDL2_IMAGE_INCLUDE_DIRS}
    ${SDL2_MIXER_INCLUDE_DIRS}
   # ${SDL2_TTF_INCLUDE_DIRS}
    /usr/local/pspdev/psp/include
    src/
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    ${SDL2_LIBRARIES}
    ${SDL2_IMAGE_LIBRARIES}
    ${SDL2_MIXER_LIBRARIES}
   # ${SDL2_TTF_LIBRARIES}
    lua
)

# Create an EBOOT.PBP file
create_pbp_file(
    TARGET ${PROJECT_NAME}
    ICON_PATH        ${CMAKE_SOURCE_DIR}/pbp_assets/ICON0.PNG
    BACKGROUND_PATH  ${CMAKE_SOURCE_DIR}/pbp_assets/PIC1.PNG
    PREVIEW_PATH     ${CMAKE_SOURCE_DIR}/pbp_assets/PIC0.PNG
    TITLE ${PROJECT_NAME}
    VERSION 01.00
)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
    ${PNG_ASSETS}
    ${CMAKE_BINARY_DIR}
)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
    ${OGG_ASSETS}
    ${CMAKE_BINARY_DIR}
)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
    ${LMAP_ASSETS}
    ${CMAKE_BINARY_DIR}
)