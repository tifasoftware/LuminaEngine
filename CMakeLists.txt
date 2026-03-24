cmake_minimum_required(VERSION 3.11)

if(APPLE)
    set(CMAKE_OSX_ARCHITECTURES "arm64;x86_64" CACHE STRING "")
    set(CMAKE_OSX_DEPLOYMENT_TARGET "11.0" CACHE STRING "")
endif()

project(LuminaEngine)

if(APPLE)
    set(SDL2_LIBRARIES "-framework SDL2")
    set(SDL2_IMAGE_LIBRARIES "-framework SDL2_image")
    set(SDL2_MIXER_LIBRARIES "-framework SDL2_mixer")
    set(SDL2_INCLUDE_DIRS "/Library/Frameworks/SDL2.framework/Headers")
    set(SDL2_IMAGE_INCLUDE_DIRS "/Library/Frameworks/SDL2_image.framework/Headers")
    set(SDL2_MIXER_INCLUDE_DIRS "/Library/Frameworks/SDL2_mixer.framework/Headers")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -F/Library/Frameworks")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -F/Library/Frameworks")
endif()

file (GLOB_RECURSE SOURCES "src/*.cpp")
file (GLOB PNG_ASSETS "assets/*.png")
file (GLOB OGG_ASSETS "assets/*.ogg")
file (GLOB WAV_ASSETS "assets/*.wav")
file (GLOB LMAP_ASSETS "assets/*.lmap")


add_executable(${PROJECT_NAME} ${SOURCES})

if (NOT PSP)
    add_subdirectory(src_tools/lmap_compile)
    add_subdirectory(src_tools/lmap_info)
else()
    target_compile_options(${PROJECT_NAME} PRIVATE "-F/Library/Frameworks")
    target_link_options(${PROJECT_NAME} PRIVATE "-F/Library/Frameworks")
endif()

if (NOT APPLE)
    include(FindPkgConfig)

    pkg_search_module(SDL2 REQUIRED sdl2)
    pkg_search_module(SDL2_IMAGE REQUIRED SDL2_image)
    pkg_search_module(SDL2_MIXER REQUIRED SDL2_mixer)
    #pkg_search_module(SDL2_TTF REQUIRED SDL2_ttf)
    #pkg_search_module(LUA REQUIRED lua5.4)
else()
    target_sources(${PROJECT_NAME} PRIVATE
        ${PNG_ASSETS}
        ${OGG_ASSETS}
        ${WAV_ASSETS}
        ${LMAP_ASSETS})
    set_source_files_properties(
            ${PNG_ASSETS} ${OGG_ASSETS} ${WAV_ASSETS} ${LMAP_ASSETS}
            PROPERTIES MACOSX_PACKAGE_LOCATION "Resources"
    )
    target_compile_options(${PROJECT_NAME} PRIVATE "-F/Library/Frameworks")
    target_link_options(${PROJECT_NAME} PRIVATE "-F/Library/Frameworks")
    target_link_libraries(${PROJECT_NAME} PRIVATE
            "${CMAKE_SOURCE_DIR}/libs/liblua5.4.dylib"
    )
endif()

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
        #lua
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
            # Bundle identity (your existing ones)
            MACOSX_BUNDLE TRUE
            MACOSX_BUNDLE_BUNDLE_NAME ${PROJECT_NAME}
            MACOSX_BUNDLE_BUNDLE_VERSION "1.0"
            MACOSX_BUNDLE_SHORT_VERSION_STRING "1.0"
            MACOSX_BUNDLE_GUI_IDENTIFIER "org.infitechppc.${PROJECT_NAME}"

            # ADD: Xcode universal binary settings
            XCODE_ATTRIBUTE_ARCHS "arm64 x86_64"
            XCODE_ATTRIBUTE_ONLY_ACTIVE_ARCH "NO"
            XCODE_ATTRIBUTE_VALID_ARCHS "arm64 x86_64"
            XCODE_ATTRIBUTE_MACOSX_DEPLOYMENT_TARGET "11.0"
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
    install(CODE "
        execute_process(COMMAND dylibbundler
            -od -b
            -x ${CMAKE_BINARY_DIR}/${PROJECT_NAME}.app/Contents/MacOS/${PROJECT_NAME}
            -d ${CMAKE_BINARY_DIR}/${PROJECT_NAME}.app/Contents/Frameworks/
            -p @executable_path/../Frameworks/
        )
    ")

    # KEEP: your existing asset bundling
    set_source_files_properties(${PNG_ASSETS} ${OGG_ASSETS} ${WAV_ASSETS} ${LMAP_ASSETS}
            PROPERTIES MACOSX_PACKAGE_LOCATION Resources
    )
endif()

if (NOT APPLE)
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