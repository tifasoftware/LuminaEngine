cmake_minimum_required(VERSION 3.11)

project(psprpg)

file (GLOB_RECURSE SOURCES "src/*.cpp")
file (GLOB PNG_ASSETS "assets/*.png")

add_executable(${PROJECT_NAME} ${SOURCES})

include(FindPkgConfig)
pkg_search_module(SDL2 REQUIRED sdl2)
pkg_search_module(SDL2_IMAGE REQUIRED SDL2_image)
#pkg_search_module(LUA REQUIRED lua5.4)

target_include_directories(${PROJECT_NAME} PRIVATE
    ${SDL2_INCLUDE_DIRS}
    ${SDL2_IMAGE_INCLUDE_DIRS}
    /usr/local/pspdev/psp/include
    src/
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    ${SDL2_LIBRARIES}
    ${SDL2_IMAGE_LIBRARIES}
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