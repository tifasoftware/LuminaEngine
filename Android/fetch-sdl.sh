#!/usr/bin/env bash

cd app/jni

git clone -b SDL2 https://github.com/libsdl-org/SDL.git
git clone -b SDL2 https://github.com/libsdl-org/SDL_image.git
git clone -b SDL2 https://github.com/libsdl-org/SDL_mixer.git

cd ../..