cmake_minimum_required(VERSION 3.6)

project(LuminaAndroid)

# dumb ovveride to get rid of CMakeCache
set(LUMINA_VERSION 0.19)

# armeabi-v7a requires cpufeatures library
if (CMAKE_ANDROID_ARCH_ABI STREQUAL "armeabi-v7a")
    include(AndroidNdkModules)
    android_ndk_import_module_cpufeatures()
endif()


# SDL sources are in a subfolder named "SDL"
add_subdirectory(SDL)

# Compilation of companion libraries
add_subdirectory(SDL_image)
add_subdirectory(SDL_mixer)
#add_subdirectory(SDL_ttf)

# Your game and its CMakeLists.txt are in a subfolder named "src"
add_subdirectory(src)

