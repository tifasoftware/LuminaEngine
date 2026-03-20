#include "entity.h"
#include <cstring>

#include "TileMap.h"


const char * Entity::getProperty(const char *key) {
    return properties[getPropertyIndex(key)].value;
}

int Entity::getPropertyIndex(const char *key) {
    for (int i = 0; i < MAX_PROPERTIES; i++) {
        if (strcmp(properties[i].key, key) == 0) return i;
    }
    return -1;
}

bool Entity::hasProperty(const char *key) {
    if (getPropertyIndex(key) != -1) return true;
    return false;
}

Entity* Entity::spawnEntity(EntityDef def) {

    if (def.type == NO_ENTITY) return nullptr;
    Entity* returnEntity = new Entity();

    returnEntity->x = def.x;
    returnEntity->y = def.y;
    returnEntity->w = def.width;
    returnEntity->h = def.height;
    memcpy(returnEntity->properties, def.properties, sizeof(def.properties));
    returnEntity->type = def.type;
    returnEntity->initializeSprite(-1);

    return returnEntity;
}

bool Entity::isInTrigger(int charX, int charY) {
    if (charX > x && charX < (x + w) && charY > y && charY < (y + h)) return true;
    return false;
}

bool Entity::canBeDrawn(int screenOffsetX, int screenOffsetY) {
    if (sprite == nullptr) return false;
    if (x + w >= screenOffsetX && y + h >= screenOffsetY && x < (screenOffsetX + SCREEN_W) && y < (screenOffsetY + SCREEN_H)) return true;
    return false;
}

void Entity::draw(Renderer *r, int screenOffsetX, int screenOffsetY) {
    if (canBeDrawn(screenOffsetX, screenOffsetY)) {
        //r->drawSprite(texIndex, x - screenOffsetX, y - screenOffsetY);
        sprite->draw(x - screenOffsetX, y - screenOffsetY, r);
    }
}

void Entity::initializeSprite(int ti) {
    if (sprite != nullptr) delete sprite;
    if (type == INTERACT_NPC) {
        sprite = new CharacterSprite(ti);
    } else {
        sprite = new Sprite(ti, w, h);
    }
}

void Entity::disposeSprite() {
    if (sprite != nullptr) delete sprite;
    sprite = nullptr;
}
