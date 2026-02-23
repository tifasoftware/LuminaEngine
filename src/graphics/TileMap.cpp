#include <SDL.h>
#include <SDL_image.h>
#include <pspkernel.h>
#include <pspdisplay.h>
#include <graphics/TileMap.h>

TileMap::TileMap(const char* file, Renderer* r)
{
    renderer = r;

    if (loadFromFile(file)) {

    } else {
        r->loadTexture("grass.png");

        for (int x = 0; x < tileW; x++){
            for (int y = 0; y < tileH; y++){
                tiles[x][y] = 0;
            }
        }
    }
}

void TileMap::drawMap()
{
    for (int x = 0; x < tileW; x++){
        for (int y = 0; y < tileH; y++){
            renderer->drawTile(tiles[x][y], x * tileSize, y * tileSize);
        }
    }
}

bool TileMap::loadFromFile(const char* file)
{
    FILE* f = fopen(file, "r");
    if (!f) {
        SDL_Log("TileMap: failed to open %s", file);
        return false;
    }

    char line[256];

    fgets(line, sizeof(line), f);
    if (strncmp(line, "LMAP", 4) != 0){
        SDL_Log("TileMap: failed to open %s", file);
        fclose(f);
        return false;
    }

    parse_textures(f);
    parse_layout(f);

    fclose(f);
    return true;
}

void TileMap::parse_textures(FILE* file)
{
    char line[256];
    while (fgets(line, sizeof(line), file))
    {
        line[strcspn(line, "\r\n")] = 0;

        if (strcmp(line, "LAYOUT") == 0)
            break;

        renderer->loadTexture(line);
    }
}

void TileMap::parse_layout(FILE* file)
{
    char line[256];
    int y = 0;
    
    while (fgets(line, sizeof(line), file))
    {
        line[strcspn(line, "\r\n")] = 0;
        if (strlen(line) == 0) continue;

        int x = 0;
        char* token = strtok(line, ",");
        while (token != nullptr && x < tileW) {
            tiles[x][y] = atoi(token);
            x++;
            token = strtok(nullptr, ",");
        }

        y++;
        if (y >= tileH) break;
    }
}
