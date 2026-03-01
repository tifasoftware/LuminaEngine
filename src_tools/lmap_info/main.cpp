#include <formats/lmap.h>
#include <iostream>
#include <stdio.h>

using namespace std;

int tiles[64][64];

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        cout << "USAGE: lmap_info [INPUT.lmap]\n";
        return -1;
    }
    const char* lmapfile = argv[1];

    LMAPHeader lmap;
    FILE* in = fopen(lmapfile, "rb");
    fread(&lmap, sizeof(LMAPHeader), 1, in);
    fclose(in);

    cout << "LMAP\n======\n";
    cout << "Tileset: ";
    cout << lmap.tileset;
    cout << "\nGRID\n";
    
    for (int i = 0; i < 64; i++)
    {
        cout << lmap.tiles[i];
        cout << " ";
    }
    cout << endl;
}