#include "entity.h"

#include "warppoint.h"

Entity* Entity::spawnEntity(EntityDef def) {
    Entity* returnEntity = nullptr;
    switch (def.type) {
        case TRIGGER_BATTLEFIELD:
            break;
        case TRIGGER_LUA:
            break;
        case TRIGGER_WARP:
            returnEntity = WarpPoint::createWarpPoint(def.file);
            break;
        case INTERACT_LUA:
            break;
        case INTERACT_NPC:
            break;
        case NO_ENTITY:
            return nullptr;
        default:
            break;
    }

    if (returnEntity == nullptr) return returnEntity;

    returnEntity->x = def.x;
    returnEntity->y = def.y;
    returnEntity->w = def.width;
    returnEntity->h = def.height;
    memcpy(returnEntity->properties, def.properties, sizeof(def.properties));
    returnEntity->type = def.type;

    return returnEntity;
}
