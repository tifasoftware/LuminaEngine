#include <formats/lmap.h>
#include <common/types.h>
#include <iostream>
#include <stdio.h>

using namespace std;

int tiles[64][64];

const char* convertToString(CollisionType ct)
{
    switch (ct)
    {
        case NONE:
        return "0";
        
        case NORTH:
        return "U";

        case SOUTH:
        return "S";

        case EAST:
        return "E";

        case WEST:
        return "W";

        default:
        break;
    }

    return "NONE";
}

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

    cout << "\nCOLLIDE\n";
    
    for (int i = 0; i < 8; i++)
    {
        cout << convertToString(lmap.colTile[i]);
        cout << " ";
    }

    cout << "\nReferenced Files\n";

    for (int i = 0; i < 64; i++) {
        if (lmap.entities[i].type != NO_ENTITY) {
            cout << "\n";
            cout << lmap.entities[i].file;
            cout << "\n";
        }
    }

    cout << endl;
}