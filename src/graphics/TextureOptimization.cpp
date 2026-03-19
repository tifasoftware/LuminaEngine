#include "TextureOptimization.h"

#include <cstring>

int TextureOptimization::getIndex(char file[64]) {
    for (int i = 0; i < 64; i++) {
        if (strcmp(file, files[i]) == 0) return indexes[i];
    }
    return -1;
}

int TextureOptimization::getIndex(const char *file) {
    char fileName[64];
    strncpy(fileName, file, 63);
    return getIndex(fileName);
}

void TextureOptimization::registerFileName(char file[64], int index) {
    strcpy(files[fileCount], file);
    indexes[fileCount] = index;
    fileCount++;
}

void TextureOptimization::registerFileName(const char* file, int index) {
    char fileName[64];
    strncpy(fileName, file, 63);
    registerFileName(fileName, index);
}

TextureOptimization::TextureOptimization() {
    fileCount = 0;

    for (int i = 0; i < 64; i++) {
        indexes[i] = -1;
        strcpy(files[i], "");
    }
}
