#include <formats/lmap.h>
#include <common/types.h>
#include <json.hpp>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include "conversion.h"
#include "parsing.h"
#include "global.h"

using namespace std;
using json = nlohmann::json;

int tiles[64][64];
CollisionType colType[256];
char tileAtlas[64];
Entity entities[64];

int main(int argc, char *argv[])
{
    if (argc != 4)
    {
        cout << "USAGE: lmap_compile [TMJFILE.tmj] [TILEMAP.lad] [OUTPUT.lmap]\n";
        cout << endl;
        return -1;
    }
    const char* csvfile = argv[1];
    const char* tilemapfile = argv[2];
    const char* outputfile = argv[3];

    LMAPHeader lmap;

    memcpy(lmap.magic, "LMAP", 4);
    lmap.height = 64;
    lmap.width = 64;
    lmap.version = 2;

    parse_layout(csvfile);

    /*cout << "\nParsing CSV\n";
    FILE* f = fopen(csvfile, "r");
    parse_layout(f);
    fclose(f);*/

    cout << "Parsing Tilemap Definition\n";
    FILE* f = fopen(tilemapfile, "r");
    bool isGood = parse_tilemapdef(f);
    fclose(f);

    //lmap.colTile = colType;
    memcpy(lmap.colTile, colType, sizeof(colType));
    memcpy(lmap.entities, entities, sizeof(entities));
    strncpy(lmap.tileset, tileAtlas, 63);

    if (!isGood)
    {
        cout << "Tilemap Invalid\nCompilation Aborted\n";
        cout << endl;
        return -1;
    }


    int offset = 0;

    for (int x = 0; x < 64; x++)
    {
        for (int y = 0; y < 64; y++)
        {
            lmap.tiles[offset + y] = tiles[x][y];
        }
        offset += 64;
    }


    cout << "\nGRID\n";
    
    for (int i = 0; i < 64; i++)
    {
        cout << lmap.tiles[i];
    }

    FILE* out = fopen(outputfile, "wb");

    fwrite(&lmap, sizeof(LMAPHeader), 1, out);
    fclose(out);


    cout << endl;

    return 0;
}

