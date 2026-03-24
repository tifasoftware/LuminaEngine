cmake_minimum_required(VERSION 3.11)

project(LuminaEngine)

if(APPLE)
    set(SDL2_LIBRARIES "-framework SDL2")
    set(SDL2_IMAGE_LIBRARIES "-framework SDL2_image")
    set(SDL2_MIXER_LIBRARIES "-framework SDL2_mixer")
    set(SDL2_INCLUDE_DIRS "/Library/Frameworks/SDL2.framework/Headers")
    set(SDL2_IMAGE_INCLUDE_DIRS "/Library/Frameworks/SDL2_image.framework/Headers")
    set(SDL2_MIXER_INCLUDE_DIRS "/Library/Frameworks/SDL2_mixer.framework/Headers")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -F/Library/Frameworks")
endif()

file (GLOB_RECURSE SOURCES "src/*.cpp")
file (GLOB PNG_ASSETS "assets/*.png")
file (GLOB OGG_ASSETS "assets/*.ogg")
file (GLOB WAV_ASSETS "assets/*.wav")
file (GLOB LMAP_ASSETS "assets/*.lmap")


add_executable(${PROJECT_NAME} ${SOURCES})

if (APPLE)
    include_directories(/opt/homebrew/include)
    link_directories(/opt/homebrew/lib)
endif()

if (NOT PSP)
    add_subdirectory(src_tools/lmap_compile)
    add_subdirectory(src_tools/lmap_info)
endif()

include(FindPkgConfig)

pkg_search_module(SDL2 REQUIRED sdl2)
pkg_search_module(SDL2_IMAGE REQUIRED SDL2_image)
pkg_search_module(SDL2_MIXER REQUIRED SDL2_mixer)
#pkg_search_module(SDL2_TTF REQUIRED SDL2_ttf)
#pkg_search_module(LUA REQUIRED lua5.4)

if (PSP)
    target_include_directories(${PROJECT_NAME} PRIVATE
        ${SDL2_INCLUDE_DIRS}
        ${SDL2_IMAGE_INCLUDE_DIRS}
        ${SDL2_MIXER_INCLUDE_DIRS}
    # ${SDL2_TTF_INCLUDE_DIRS}
        /usr/local/pspdev/psp/include
        src/
    )
else()
    target_include_directories(${PROJECT_NAME} PRIVATE
            ${SDL2_INCLUDE_DIRS}
            ${SDL2_IMAGE_INCLUDE_DIRS}
            ${SDL2_MIXER_INCLUDE_DIRS}
            src/
    )
endif ()

target_link_libraries(${PROJECT_NAME} PRIVATE
        ${SDL2_LIBRARIES}
        ${SDL2_IMAGE_LIBRARIES}
        ${SDL2_MIXER_LIBRARIES}
        # ${SDL2_TTF_LIBRARIES}
        lua
)

if (PSP)
    # Create an EBOOT.PBP file
    create_pbp_file(
        TARGET ${PROJECT_NAME}
        ICON_PATH        ${CMAKE_SOURCE_DIR}/pbp_assets/ICON0.PNG
        BACKGROUND_PATH  ${CMAKE_SOURCE_DIR}/pbp_assets/PIC1.PNG
        PREVIEW_PATH     ${CMAKE_SOURCE_DIR}/pbp_assets/PIC0.PNG
        TITLE ${PROJECT_NAME}
        VERSION 01.00
    )

endif()

if(APPLE)
    set_target_properties(${PROJECT_NAME} PROPERTIES
            MACOSX_BUNDLE TRUE
            MACOSX_BUNDLE_BUNDLE_NAME ${PROJECT_NAME}
            MACOSX_BUNDLE_BUNDLE_VERSION "1.0"
            MACOSX_BUNDLE_SHORT_VERSION_STRING "1.0"
            MACOSX_BUNDLE_GUI_IDENTIFIER "org.infitechppc.${PROJECT_NAME}"
    )
    install(CODE "
        execute_process(COMMAND dylibbundler
            -od -b
            -x ${CMAKE_BINARY_DIR}/${PROJECT_NAME}.app/Contents/MacOS/${PROJECT_NAME}
            -d ${CMAKE_BINARY_DIR}/${PROJECT_NAME}.app/Contents/Frameworks/
            -p @executable_path/../Frameworks/
        )
    ")
    set_source_files_properties(${PNG_ASSETS} ${OGG_ASSETS} ${WAV_ASSETS} ${LMAP_ASSETS}
            PROPERTIES MACOSX_PACKAGE_LOCATION Resources
    )
endif()

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
    ${WAV_ASSETS}
    ${CMAKE_BINARY_DIR}
)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
    ${LMAP_ASSETS}
    ${CMAKE_BINARY_DIR}
)