#pragma once

struct LSAVHeader
{
    char magic[4];
    char gameID[256];
    char currMap[64];
    char music[64];

    int charX;
    int charY;
    int scrnX;
    int scrnY;
};

class LSAVLoader
{
public:
    LSAVLoader() : file("") {}
    LSAVLoader(const char* file);
    LSAVHeader* load();

private:
    const char* file;
};

class LSAVWriter {
    public:
    LSAVWriter() : file("") {}
    LSAVWriter(const char* file);
    int write(LSAVHeader* header);

    private:
    const char* file;
};