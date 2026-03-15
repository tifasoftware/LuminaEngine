#include "parsing.h"

#include "collision_convert.h"

using namespace std;
using json = nlohmann::json;

void parse_layout(const char* file)
{
    std::ifstream f(file);
    json data = json::parse(f);

    for (auto& layer : data["layers"]) {
        std::string type = layer["type"];

        if (type == "tilelayer") {
            auto& layerTiles = layer["data"];

            for (int x = 0; x < 64; x++) {
                for (int y = 0; y < 64; y++) {
                    int t = (layerTiles[y * 64 + x]);
                    tiles[x][y] = t - 1;
                }
            }
        }
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