#include "entity.h"
#include <cstring>


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

    return returnEntity;
}

bool Entity::isInTrigger(int charX, int charY) {
    if (charX > x && charX < (x + w) && charY > y && charY < (y + h)) return true;
    return false;
}
