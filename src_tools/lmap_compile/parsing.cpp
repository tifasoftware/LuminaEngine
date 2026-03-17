#include "parsing.h"

#include "conversion.h"

using namespace std;
using json = nlohmann::json;

void parse_layout(const char* file)
{
    int entityCount = 0;
    std::ifstream f(file);
    json data = json::parse(f);

    for (auto& layer : data["layers"]) {
        std::string type = layer["type"];
        int id = layer["id"];

        if (type == "tilelayer" && id == 1) {
            auto& layerTiles = layer["data"];

            for (int x = 0; x < 64; x++) {
                for (int y = 0; y < 64; y++) {
                    int t = (layerTiles[y * 64 + x]);
                    tiles[x][y] = t - 1;
                }
            }
        } else if (type == "tilemap" && id > 1) {
            auto& layerTiles = layer["data"];

            for (int x = 0; x < 64; x++) {
                for (int y = 0; y < 64; y++) {
                    //int t = (layerTiles[y * 64 + x]);
                    //tiles[x][y] = t - 1;
                }
            }
        } else if (type == "objectgroup") {
            for (auto& object : layer["objects"]) {
                std::string objectType = object["type"];
                std::string objectFile = "unknown";
                std::string objectOrientation = "all";
                std::string objectName = object["name"];

                int x = object["x"].get<int>();
                int y = object["y"].get<int>();

                int w = object.contains("w") ? object["w"].get<int>() : 16;
                int h = object.contains("h") ? object["h"].get<int>() : 16;

                for (auto& property : object["properties"]) {
                    std::string propertyName = property["name"];
                    std::string value = property["value"];

                    if (propertyName == "lua" || propertyName == "map") objectFile = value;
                    if (propertyName == "orientation") objectOrientation = value;
                }

                EntityDef entity = EntityDef();

                const char* name_c = objectName.c_str();
                strncpy(entity.name, name_c, 63);
                entity.orientation = stringToOrientation(objectOrientation.c_str());
                entity.type = stringToEntityType(objectType.c_str());
                const char* file_c = objectFile.c_str();
                strncpy(entity.file, file_c, 127);
                entity.x = x;
                entity.y = y;
                entity.width = w;
                entity.height = h;

                entities[entityCount] = entity;
                entityCount++;
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

        colType[i] = stringToCollisionType(line);

        i++;
    }

    return true;

}