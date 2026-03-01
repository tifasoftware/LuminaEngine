#include <formats/lmap.h>
#include <iostream>
#include <stdio.h>

using namespace std;

int tiles[64][64];

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

int main(int argc, char *argv[])
{
    if (argc != 4)
    {
        cout << "USAGE: lmap_compile [CSVFILE.csv] [TILEMAP.png] [OUTPUT.lmap]\n";
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
    strncpy(lmap.tileset, tilemapfile, 63);
    lmap.tileset[63] = '\0';

    FILE* f = fopen(csvfile, "r");
    parse_layout(f);
    fclose(f);


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

