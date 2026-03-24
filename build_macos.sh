#!/bin/zsh

cmake .. -DCMAKE_OSX_ARCHITECTURES=arm64 -B build-arm64
cmake .. -DCMAKE_OSX_ARCHITECTURES=x86_64 -B build-x86_64

cmake --build build-arm64
cmake --build build-x86_64

lipo -create build-arm64/LuminaEngine build-x86_64/LuminaEngine -output LuminaEngine-universal
