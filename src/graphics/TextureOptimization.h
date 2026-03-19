#pragma once
#include "Renderer.h"
#include "Texture.h"

class TextureOptimization {
    public:
    TextureOptimization();
    void registerFileName(char file[64], int index);
    void registerFileName(const char* file, int index);
    int getIndex(char file[64]);
    int getIndex(const char* file);

    private:
    char files[64][64];
    int indexes[64];
    int fileCount;
};