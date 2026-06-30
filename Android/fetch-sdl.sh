#!/usr/bin/env bash

cd app/jni

git clone -b release-2.26.x https://github.com/libsdl-org/SDL.git
git clone -b SDL2 https://github.com/libsdl-org/SDL_image.git
git clone -b SDL2 https://github.com/libsdl-org/SDL_mixer.git

cd SDL
\rm -rf .git
cd ..
cd SDL_image
\rm -rf .git
cd external
./download.sh
cd ../..
cd SDL_mixer
\rm -rf .git
cd external
./download.sh
cd ../..

mkdir include
cp -r SDL/include include/SDL2
cp SDL_image/include/SDL_image.h include/SDL2/SDL_image.h
cp SDL_mixer/include/SDL_mixer.h include/SDL2/SDL_mixer.h

cd ../..
