#include "parsing.h"

#include "conversion.h"

using namespace std;
using json = nlohmann::json;

void parse_layout(const char* file)
{
    int entityCount = 0;
    int spawnCount = 0;
    std::ifstream f(file);
    json data = json::parse(f);

    if (data.contains("properties")) {
        for (auto& property: data["properties"]) {
            std::string propertyName = property["name"];
            std::string value = property["value"];

            if (propertyName == "music") {
                strncpy(music, value.c_str(), 63);
            } else if (propertyName == "skybox") {
                strncpy(skybox, value.c_str(), 63);
            } else if (propertyName == "atlas") {
                strncpy(tileAtlas, value.c_str(), 63);
            }
        }
    }

    for (auto& layer : data["layers"]) {
        std::string type = layer["type"];
        std::string layerClass = layer.contains("class") ? layer["class"] : "unknown";
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
        } else if (type == "objectgroup" && layerClass == "entities") {
            for (auto& object : layer["objects"]) {
                int propertyCount = 0;
                std::string objectType = object["type"];
                std::cout << objectType << std::endl;
                std::string objectFile = "unknown";
                std::string objectOrientation = "all";
                std::string objectName = object["name"];

                int x = object["x"].get<int>();
                int y = object["y"].get<int>();

                int w = 2;
                int h = 2;

                if (object.contains("width")) w = object["width"].get<int>();
                if (object.contains("height")) h = object["height"].get<int>();

                EntityDef entity = EntityDef();

                const char* name_c = objectName.c_str();
                strncpy(entity.name, name_c, 63);
                entity.x = x;
                entity.y = y;
                entity.width = w;
                entity.height = h;

                for (auto& property : object["properties"]) {
                    std::string propertyName = property["name"];
                    std::string value = property["value"];

                    //if (propertyName == "lua" || propertyName == "map") objectFile = value;
                    if (propertyName == "orientation") {
                        objectOrientation = value;
                    } else {
                        strncpy(entity.properties[propertyCount].key, propertyName.c_str(), 63);
                        strncpy(entity.properties[propertyCount].value, value.c_str(), 127);
                    }
                    propertyCount++;
                }

                entity.orientation = stringToOrientation(objectOrientation.c_str());
                entity.type = stringToEntityType(objectType.c_str());
                const char* file_c = objectFile.c_str();
                //strncpy(entity.file, file_c, 127);

                entities[entityCount] = entity;
                entityCount++;
            }
        } else if (type == "objectgroup" && layerClass == "spawn") {
            for (auto& object : layer["objects"]) {
                std::string spawnName = object["name"];
                int x = object["x"].get<int>();
                int y = object["y"].get<int>();

                SpawnDef spawn = SpawnDef();
                spawn.location.x = x;
                spawn.location.y = y;
                strncpy(spawn.name, spawnName.c_str(), 63);

                spawns[spawnCount] = spawn;
                spawnCount++;
            }
        }
    }
    while (entityCount < 64) {
        EntityDef entity = EntityDef();
        entity.type = NO_ENTITY;

        entities[entityCount] = entity;

        entityCount++;
    }

    while (spawnCount < 16) {
        SpawnDef spawn = SpawnDef();
        spawn.location.x = 64;
        spawn.location.y = 64;
        strncpy(spawn.name, "undefined", 63);

        spawns[spawnCount] = spawn;
        spawnCount++;
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