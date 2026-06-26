add_executable(weiss main.cpp)

set_target_properties(weiss PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
)

target_link_directories(weiss PRIVATE
        "$ENV{DEVKITPRO}/libogc/lib"
        "$ENV{DEVKITPRO}/portlibs/gamecube/lib"
)
target_link_libraries(weiss PRIVATE
        SDL2 SDL2_image SDL2_mixer
        lua
        SDL2
)

ogc_create_dol(
        weiss
)