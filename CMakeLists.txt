cmake_minimum_required(VERSION 3.11)

set(3DS OFF CACHE BOOL "Build for 3DS")
set(SDL1_OVERRIDE OFF CACHE BOOL "Debug for SDL1")
set(LE32BIT OFF CACHE BOOL "Build for 32-bit")

if(3DS)
    add_definitions(-D__3DS__)
    add_definitions(-DLIB_SDL1)
    set(ROMFS_DIR "${CMAKE_SOURCE_DIR}/assets")
endif()

if(SDL1_OVERRIDE)
    add_definitions(-DLIB_SDL1)
endif()

if(APPLE)
    if(LE32BIT)
        set(CMAKE_OSX_ARCHITECTURES "x86_64" CACHE STRING "")
        set(CMAKE_OSX_DEPLOYMENT_TARGET "10.6" CACHE STRING "")
    else()
        set(CMAKE_OSX_ARCHITECTURES "arm64;x86_64" CACHE STRING "")
        set(CMAKE_OSX_DEPLOYMENT_TARGET "10.11" CACHE STRING "")
    endif()
endif()

project(LuminaEngine)

if(APPLE)
    if (SDL1_OVERRIDE)
        set(SDL_LIBRARIES "/usr/local/lib")
        set(SDL_INCLUDE_DIRS "/usr/local/include/SDL")
    else()
        set(SDL2_LIBRARIES "-framework SDL2")
        set(SDL2_IMAGE_LIBRARIES "-framework SDL2_image")
        set(SDL2_MIXER_LIBRARIES "-framework SDL2_mixer")
        set(SDL2_INCLUDE_DIRS "/Library/Frameworks/SDL2.framework/Headers")
        set(SDL2_IMAGE_INCLUDE_DIRS "/Library/Frameworks/SDL2_image.framework/Headers")
        set(SDL2_MIXER_INCLUDE_DIRS "/Library/Frameworks/SDL2_mixer.framework/Headers")
    endif()
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -F/Library/Frameworks")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -F/Library/Frameworks")

    set(APP_ICON "${CMAKE_SOURCE_DIR}/pbp_assets/AppIcon.icns")
endif()

if (WIN32)
    if (LE32BIT)
        set(SDL2_DIR "${CMAKE_SOURCE_DIR}/libs/mingw/i686-w64-mingw32")
    else()
        set(SDL2_DIR "${CMAKE_SOURCE_DIR}/libs/mingw/x86_64-w64-mingw32")
    endif()

    set(SDL2_INCLUDE_DIRS "${SDL2_DIR}/include")
    set(SDL2_IMAGE_INCLUDE_DIRS "${SDL2_DIR}/include")
    set(SDL2_MIXER_INCLUDE_DIRS "${SDL2_DIR}/include")

    set(SDL2_LIBRARIES
            "${SDL2_DIR}/lib/libSDL2main.a"
            "${SDL2_DIR}/lib/libSDL2.dll.a"
    )
    set(SDL2_IMAGE_LIBRARIES "${SDL2_DIR}/lib/libSDL2_image.dll.a")
    set(SDL2_MIXER_LIBRARIES "${SDL2_DIR}/lib/libSDL2_mixer.dll.a")

    set(APP_ICON_RC "${CMAKE_SOURCE_DIR}/pbp_assets/app.rc")
endif()

file (GLOB_RECURSE SOURCES "src/*.cpp")
file (GLOB LUA_SOURCES "libs/lua-5.5.0/src/*.c")
file (GLOB LUA_ASSETS "assets/*.lua")
file (GLOB PNG_ASSETS "assets/*.png")
file (GLOB OGG_ASSETS "assets/*.ogg")
file (GLOB WAV_ASSETS "assets/*.wav")
file (GLOB LMAP_ASSETS "assets/*.lmap")


add_executable(${PROJECT_NAME} ${SOURCES})

add_library(lua STATIC ${LUA_SOURCES})

target_include_directories(lua PUBLIC
    external/lua/src
)

if (NOT (PSP OR 3DS))
    add_subdirectory(src_tools/lmap_compile)
    add_subdirectory(src_tools/lmap_info)
    add_subdirectory(src_tools/lua_test)
else()
    target_compile_definitions(lua PRIVATE LUA_32BITS)
endif()

if(3DS)
    set(SDL2_INCLUDE_DIRS "$ENV{DEVKITPRO}/portlibs/3ds/include")
    set(SDL2_IMAGE_INCLUDE_DIRS "$ENV{DEVKITPRO}/portlibs/3ds/include")
    set(SDL2_MIXER_INCLUDE_DIRS "$ENV{DEVKITPRO}/portlibs/3ds/include")

    set(PORT_LIBRARIES jpeg png z mad mikmod vorbisidec ogg)
    set(SDL2_LIBRARIES SDL)
    set(SDL2_IMAGE_LIBRARIES SDL_image)
    set(SDL2_MIXER_LIBRARIES SDL_mixer)

    set(CTRU_LIBRARIES citro3d citro2d ctru m)
    set_target_properties(${PROJECT_NAME} PROPERTIES SUFFIX ".3dsx")
elseif (NOT (APPLE OR WIN32))
    find_package(PkgConfig QUIET)

    if (SDL1_OVERRIDE)
        message(STATUS "SDL1_OVERRIDE enabled, using SDL1")

        if (PKG_CONFIG_FOUND)
            pkg_check_modules(SDL1 QUIET IMPORTED_TARGET sdl)
        endif()

        if (SDL1_FOUND)
            message(STATUS "Found SDL1 via pkg-config: ${SDL1_VERSION}")
            target_link_libraries(${PROJECT_NAME} PRIVATE PkgConfig::SDL1)
        else()
            find_path(SDL1_INCLUDE_DIR SDL.h
                    PATHS
                    /usr/include/SDL
                    /usr/local/include/SDL
                    /opt/local/include/SDL
                    /opt/homebrew/include/SDL
            )
            find_library(SDL1_LIBRARY
                    NAMES SDL
                    PATHS
                    /usr/lib
                    /usr/local/lib
                    /opt/local/lib
                    /opt/homebrew/lib
            )

            if (SDL1_INCLUDE_DIR AND SDL1_LIBRARY)
                message(STATUS "Found SDL1 manually: ${SDL1_LIBRARY}")
                target_include_directories(${PROJECT_NAME} PRIVATE ${SDL1_INCLUDE_DIR})
                target_link_libraries(${PROJECT_NAME} PRIVATE ${SDL1_LIBRARY})
            else()
                message(FATAL_ERROR "SDL1 not found. Install libsdl1.2-dev or equivalent.")
            endif()
        endif()

    else()
        find_package(PkgConfig REQUIRED)

        # SDL2 #
        pkg_check_modules(SDL2 sdl2)
        # SDL2_image
        pkg_check_modules(SDL2_IMAGE SDL2_image)
        # SDL2_mixer
        pkg_check_modules(SDL2_MIXER SDL2_mixer)

        # SDL2 fallback
        if (NOT SDL2_FOUND)
            find_path(SDL2_INCLUDE_DIRS
                    NAMES SDL.h
                    PATH_SUFFIXES SDL2
            )
            find_library(SDL2_LIBRARIES
                    NAMES SDL2
            )

            if (NOT SDL2_INCLUDE_DIRS OR NOT SDL2_LIBRARIES)
                message(FATAL_ERROR
                        "SDL2 not found. Install with:\n"
                        "  Fedora:  sudo dnf install SDL2-devel\n"
                        "  Ubuntu:  sudo apt install libsdl2-dev\n"
                        "  Arch:    sudo pacman -S sdl2\n"
                        "  FreeBSD: sudo pkg install sdl2\n"
                )
            endif()
        endif()

        # SDL2_image fallback
        if (NOT SDL2_IMAGE_FOUND)
            find_path(SDL2_IMAGE_INCLUDE_DIRS
                    NAMES SDL_image.h
                    PATH_SUFFIXES SDL2
            )
            find_library(SDL2_IMAGE_LIBRARIES
                    NAMES SDL2_image
            )

            if (NOT SDL2_IMAGE_INCLUDE_DIRS OR NOT SDL2_IMAGE_LIBRARIES)
                message(FATAL_ERROR
                        "SDL2_image not found. Install with:\n"
                        "  Fedora:  sudo dnf install SDL2_image-devel\n"
                        "  Ubuntu:  sudo apt install libsdl2-image-dev\n"
                        "  Arch:    sudo pacman -S sdl2_image\n"
                        "  FreeBSD: sudo pkg install sdl2_image\n"
                )
            endif()
        endif()

        # SDL2_mixer fallback
        if (NOT SDL2_MIXER_FOUND)
            find_path(SDL2_MIXER_INCLUDE_DIRS
                    NAMES SDL_mixer.h
                    PATH_SUFFIXES SDL2
            )
            find_library(SDL2_MIXER_LIBRARIES
                    NAMES SDL2_mixer
            )

            if (NOT SDL2_MIXER_INCLUDE_DIRS OR NOT SDL2_MIXER_LIBRARIES)
                message(FATAL_ERROR
                        "SDL2_mixer not found. Install with:\n"
                        "  Fedora:  sudo dnf install SDL2_mixer-devel\n"
                        "  Ubuntu:  sudo apt install libsdl2-mixer-dev\n"
                        "  Arch:    sudo pacman -S sdl2_mixer\n"
                        "  FreeBSD: sudo pkg install sdl2_mixer\n"
                )
            endif()
        endif()

        message(STATUS "SDL2 Include Dirs:       ${SDL2_INCLUDE_DIRS}")
        message(STATUS "SDL2 Libraries:          ${SDL2_LIBRARIES}")
        message(STATUS "SDL2_image Include Dirs: ${SDL2_IMAGE_INCLUDE_DIRS}")
        message(STATUS "SDL2_image Libraries:    ${SDL2_IMAGE_LIBRARIES}")
        message(STATUS "SDL2_mixer Include Dirs: ${SDL2_MIXER_INCLUDE_DIRS}")
        message(STATUS "SDL2_mixer Libraries:    ${SDL2_MIXER_LIBRARIES}")

        target_include_directories(${PROJECT_NAME} PRIVATE
                ${SDL2_INCLUDE_DIRS}
                ${SDL2_IMAGE_INCLUDE_DIRS}
                ${SDL2_MIXER_INCLUDE_DIRS}
        )
        target_link_directories(${PROJECT_NAME} PRIVATE
                ${SDL2_LIBRARY_DIRS}
                ${SDL2_IMAGE_LIBRARY_DIRS}
                ${SDL2_MIXER_LIBRARY_DIRS}
        )
        target_link_libraries(${PROJECT_NAME} PRIVATE
                ${SDL2_LIBRARIES}
                ${SDL2_IMAGE_LIBRARIES}
                ${SDL2_MIXER_LIBRARIES}
        )
        target_compile_options(${PROJECT_NAME} PRIVATE
                ${SDL2_CFLAGS_OTHER}
                ${SDL2_IMAGE_CFLAGS_OTHER}
                ${SDL2_MIXER_CFLAGS_OTHER}
        )
    endif()
endif()

if (APPLE)
    target_sources(${PROJECT_NAME} PRIVATE
        ${PNG_ASSETS}
        ${OGG_ASSETS}
        ${WAV_ASSETS}
        ${LMAP_ASSETS}
        ${LUA_ASSETS}
        ${APP_ICON}
    )
    set_source_files_properties(
            ${PNG_ASSETS} ${OGG_ASSETS} ${WAV_ASSETS} ${LMAP_ASSETS} ${LUA_ASSETS} ${APP_ICON}
            PROPERTIES MACOSX_PACKAGE_LOCATION "Resources"
    )
    target_compile_options(${PROJECT_NAME} PRIVATE "-F/Library/Frameworks")
    target_link_options(${PROJECT_NAME} PRIVATE "-F/Library/Frameworks")
endif()

if (PSP)
    target_include_directories(${PROJECT_NAME} PRIVATE
        ${SDL2_INCLUDE_DIRS}
        ${SDL2_IMAGE_INCLUDE_DIRS}
        ${SDL2_MIXER_INCLUDE_DIRS}
        libs/lua-5.5.0/src/
        /usr/local/pspdev/psp/include
        src/
    )
elseif(3DS)
    target_include_directories(${PROJECT_NAME} PRIVATE
            ${SDL2_INCLUDE_DIRS}
            ${SDL2_IMAGE_INCLUDE_DIRS}
            ${SDL2_MIXER_INCLUDE_DIRS}
            libs/lua-5.5.0/src/
            src/
            "$ENV{DEVKITPRO}/libctru/include"
    )
elseif(SDL1_OVERRIDE)
    target_include_directories(${PROJECT_NAME} PRIVATE
            ${SDL_INCLUDE_DIRS}
            libs/lua-5.5.0/src/
            src/
    )
else()
    target_include_directories(${PROJECT_NAME} PRIVATE
            ${SDL2_INCLUDE_DIRS}
            ${SDL2_IMAGE_INCLUDE_DIRS}
            ${SDL2_MIXER_INCLUDE_DIRS}
            libs/lua-5.5.0/src/
            src/
    )
endif ()

if (WIN32)
    target_link_libraries(${PROJECT_NAME} PRIVATE
	    mingw32
        ${SDL2_LIBRARIES}
        ${SDL2_IMAGE_LIBRARIES}
        ${SDL2_MIXER_LIBRARIES}
        lua
    )

    target_link_options(${PROJECT_NAME} PRIVATE
            -static-libgcc
            -static-libstdc++
            -Wl,-Bstatic -lwinpthread -Wl,-Bdynamic
    )

    target_sources(${PROJECT_NAME} PRIVATE ${APP_ICON_RC})

    set_target_properties(${PROJECT_NAME} PROPERTIES
            WIN32_EXECUTABLE TRUE  # Prevents console window
    )
elseif(3DS)
    target_link_directories(${PROJECT_NAME} PRIVATE
            "$ENV{DEVKITPRO}/libctru/lib"
            "$ENV{DEVKITPRO}/portlibs/3ds/lib"
    )
    target_link_libraries(${PROJECT_NAME} PRIVATE
            SDL SDL_image SDL_mixer
            lua
            jpeg png z mad mikmod ogg vorbisidec
            SDL
            citro3d citro2d ctru m
    )

    #dkp_add_asset_target(${PROJECT_NAME}_romfs "${CMAKE_SOURCE_DIR}/assets")

    #dkp_install_assets (${PROJECT_NAME}_romfs TARGETS
    #        "${CMAKE_SOURCE_DIR}/assets"
    #)

    ctr_generate_smdh(${PROJECT_NAME}.smdh
            NAME "${PROJECT_NAME}"
            DESCRIPTION "v${PROJECT_VERSION}"
            AUTHOR "Me!"
    )

    ctr_create_3dsx(${PROJECT_NAME}
            SMDH ${PROJECT_NAME}.smdh
            ROMFS "${CMAKE_SOURCE_DIR}/assets"
    )
elseif(LIB_SDL1)
    target_link_libraries(${PROJECT_NAME} PRIVATE
            SDL SDL_image SDL_mixer
            lua
            #jpeg png z mad mikmod ogg vorbisidec
            SDL
            lua
    )
else()
    message(STATUS "SDL Include Dirs: ${SDL_INCLUDE_DIRS}")
    target_link_libraries(${PROJECT_NAME} PRIVATE
            ${SDL2_LIBRARIES}
            ${SDL2_IMAGE_LIBRARIES}
            ${SDL2_MIXER_LIBRARIES}
            lua
    )
endif()

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
            # Bundle identity (your existing ones)
            MACOSX_BUNDLE TRUE
            MACOSX_BUNDLE_BUNDLE_NAME ${PROJECT_NAME}
            MACOSX_BUNDLE_BUNDLE_VERSION "1.0"
            MACOSX_BUNDLE_SHORT_VERSION_STRING "1.0"
            MACOSX_BUNDLE_GUI_IDENTIFIER "org.infitechppc.${PROJECT_NAME}"

            # Icons
            MACOSX_BUNDLE_ICON_FILE "AppIcon.icns"

            # ADD: Xcode universal binary settings
            XCODE_ATTRIBUTE_ARCHS "arm64 x86_64"
            XCODE_ATTRIBUTE_ONLY_ACTIVE_ARCH "NO"
            XCODE_ATTRIBUTE_VALID_ARCHS "arm64 x86_64"
            XCODE_ATTRIBUTE_MACOSX_DEPLOYMENT_TARGET "10.11"
            XCODE_ATTRIBUTE_CLANG_CXX_LANGUAGE_STANDARD "c++17"
            XCODE_ATTRIBUTE_CLANG_CXX_LIBRARY "libc++"

            # ADD: Code signing ("-" = ad-hoc for local dev)
            XCODE_ATTRIBUTE_CODE_SIGN_IDENTITY "-"
            XCODE_ATTRIBUTE_CODE_SIGN_STYLE "Automatic"

            # ADD: rpath so the binary finds embedded frameworks
            INSTALL_RPATH "@executable_path/../Frameworks"
            BUILD_WITH_INSTALL_RPATH TRUE

            # ADD: Xcode scheme working directory (so assets resolve at runtime)
            XCODE_GENERATE_SCHEME TRUE
            XCODE_SCHEME_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
    )

    # ADD: SDL2 frameworks embedded + signed in the bundle
    set_source_files_properties(
            "/Library/Frameworks/SDL2.framework"
            "/Library/Frameworks/SDL2_image.framework"
            "/Library/Frameworks/SDL2_mixer.framework"
            PROPERTIES
            MACOSX_PACKAGE_LOCATION "Frameworks"
            XCODE_FILE_ATTRIBUTES "CodeSignOnCopy"
    )
    target_sources(${PROJECT_NAME} PRIVATE
            "/Library/Frameworks/SDL2.framework"
            "/Library/Frameworks/SDL2_image.framework"
            "/Library/Frameworks/SDL2_mixer.framework"
    )

    # KEEP: your existing dylibbundler install step
    execute_process(COMMAND ditto
        /Library/Frameworks/SDL2.framework
        ${CMAKE_BINARY_DIR}/${PROJECT_NAME}.app/Contents/Frameworks/SDL2.framework
    )
    execute_process(COMMAND ditto
            /Library/Frameworks/SDL2_image.framework
            ${CMAKE_BINARY_DIR}/${PROJECT_NAME}.app/Contents/Frameworks/SDL2_image.framework
    )
    execute_process(COMMAND ditto
            /Library/Frameworks/SDL2_mixer.framework
            ${CMAKE_BINARY_DIR}/${PROJECT_NAME}.app/Contents/Frameworks/SDL2_mixer.framework
    )

    # KEEP: your existing asset bundling
    set_source_files_properties(${PNG_ASSETS} ${OGG_ASSETS} ${WAV_ASSETS} ${LMAP_ASSETS} ${LUA_ASSETS}
            PROPERTIES MACOSX_PACKAGE_LOCATION Resources
    )
endif()



if (NOT (APPLE OR 3DS))
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

    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy
            ${LUA_ASSETS}
            ${CMAKE_BINARY_DIR}
    )
endif()

if(APPLE)
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND xattr -cr "$<TARGET_BUNDLE_DIR:${PROJECT_NAME}>"
            COMMAND codesign --deep --force --sign -
            "$<TARGET_BUNDLE_DIR:${PROJECT_NAME}>/Contents/Frameworks/SDL2.framework"
            COMMAND codesign --deep --force --sign -
            "$<TARGET_BUNDLE_DIR:${PROJECT_NAME}>/Contents/Frameworks/SDL2_image.framework"
            COMMAND codesign --deep --force --sign -
            "$<TARGET_BUNDLE_DIR:${PROJECT_NAME}>/Contents/Frameworks/SDL2_mixer.framework"
            COMMAND codesign --force --sign -
            "$<TARGET_BUNDLE_DIR:${PROJECT_NAME}>"
            COMMENT "Signing frameworks and bundle..."
    )
endif()

if (WIN32)
    set(SDL2_DLL_DIR "${SDL2_DIR}/bin")

    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        # SDL2 DLLs
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${SDL2_DLL_DIR}/SDL2.dll"
            "$<TARGET_FILE_DIR:${PROJECT_NAME}>"
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${SDL2_DLL_DIR}/SDL2_image.dll"
            "$<TARGET_FILE_DIR:${PROJECT_NAME}>"
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${SDL2_DLL_DIR}/SDL2_mixer.dll"
            "$<TARGET_FILE_DIR:${PROJECT_NAME}>"
    )

    get_filename_component(MINGW_COMPILER_REAL ${CMAKE_C_COMPILER} REALPATH)
    get_filename_component(MINGW_TOOLCHAIN_DIR ${MINGW_COMPILER_REAL} DIRECTORY)
    if (LE32BIT)
        set(MINGW_DLL_DIR "${MINGW_TOOLCHAIN_DIR}/../i686-w64-mingw32/bin")
    else()
        set(MINGW_DLL_DIR "${MINGW_TOOLCHAIN_DIR}/../x86_64-w64-mingw32/bin")
    endif()

        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${MINGW_DLL_DIR}/libwinpthread-1.dll"
            $<TARGET_FILE_DIR:${PROJECT_NAME}>
    )
endif()
