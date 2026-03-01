#include <formats/lmap.h>
#include <common/types.h>
#include <iostream>
#include <stdio.h>

using namespace std;

int tiles[64][64];
CollisionType colType[256];
char tileAtlas[64];

CollisionType convertFromString(char str[])
{
    if (strcmp(str, "NORTH")) return NORTH;
    if (strcmp(str, "SOUTH")) return SOUTH;
    if (strcmp(str, "EAST")) return EAST;
    if (strcmp(str, "WEST")) return WEST;
    if (strcmp(str, "NEO")) return NEO;
    if (strcmp(str, "SEO")) return SEO;
    if (strcmp(str, "NWO")) return NWO;
    if (strcmp(str, "SWO")) return SWO;
    if (strcmp(str, "NEI")) return NEI;
    if (strcmp(str, "SEI")) return SEI;
    if (strcmp(str, "NWI")) return NWI;
    if (strcmp(str, "SWI")) return SWI;

    return NONE;
}

void parse_layout(FILE* file)
{
    char line[1024];
    int y = 0;
    
    while (fgets(line, sizeof(line), file))
    {
        line[strcspn(line, "\r\n")] = 0;
        if (strlen(line) == 0) continue;

        int x = 0;
        char* token = strtok(line, ",");
        while (token != nullptr && x < 64) {
            tiles[x][y] = atoi(token);
            x++;
            token = strtok(nullptr, ",");
        }

        y++;
        if (y >= 64) break;
    }
}

bool parse_tilemapdef(FILE* file)
{
    char line[1024];
    
    fgets(line, sizeof(line), file);
    line[strcspn(line, "r\n")] = '\0';

    if (strcmp(line, "!ATLAS") != 0) return false;

    fgets(line, sizeof(line), file);
    line[strcspn(line, "r\n")] = '\0';
    strncpy(tileAtlas, line, 64);
    tileAtlas[63] = '\0';

    int i = 0;
    while (fgets(line, sizeof(line), file))
    {
        line[strcspn(line, "r\n")] = '\0';
        if (strlen(line) == 0) continue;

        colType[i] = convertFromString(line);

        i++;
    }

    return true;

}

int main(int argc, char *argv[])
{
    if (argc != 4)
    {
        cout << "USAGE: lmap_compile [CSVFILE.csv] [TILEMAP.lad] [OUTPUT.lmap]\n";
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


    cout << "\nParsing CSV\n";
    FILE* f = fopen(csvfile, "r");
    parse_layout(f);
    fclose(f);

    cout << "Parsing Tilemap Definition\n";
    f = fopen(tilemapfile, "r");
    bool isGood = parse_tilemapdef(f);
    fclose(f);

    //lmap.colTile = colType;
    memcpy(lmap.colTile, colType, sizeof(colType));
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

