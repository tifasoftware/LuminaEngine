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
    if (getRightX() >= screenOffsetX && getBottomY() >= screenOffsetY && getLeftX() < (screenOffsetX + SCREEN_W) && getTopY() < (screenOffsetY + SCREEN_H)) return true;
    return false;
}

void Entity::draw(Renderer *r, int screenOffsetX, int screenOffsetY) {
    if (canBeDrawn(screenOffsetX, screenOffsetY)) {
        //r->drawSprite(texIndex, x - screenOffsetX, y - screenOffsetY);

        if (!centerSprite) sprite->draw(x - screenOffsetX, y - screenOffsetY, moveX, moveY, r);
        if (centerSprite) sprite->draw(getLeftX() - screenOffsetX, getTopY() - screenOffsetY, r);
    }
}

void Entity::update() {
    if (sprite != nullptr) sprite->animate(FRAME_RATE, moveX, moveY);

    x += moveX;
    y += moveY;

    //NPC Movement Test
    //This would ideally be replaced with a lua script
    if (type == INTERACT_NPC) {
        if (seconds == 0) {
            moveX = -1;
            moveY = 0;
        } else if (seconds == 1) {
            moveX = 0;
            moveY = -1;
        } else if (seconds == 2) {
            moveX = 1;
            moveY = 0;
        } else if (seconds == 3) {
            moveX = 0;
            moveY = 1;
        }

        frames++;
        if (frames >= 60) {
            seconds++;
            frames = 0;
        }
        if (seconds >= 4) {
            seconds = 0;
        }
    }
}

void Entity::initializeSprite(int ti) {
    if (sprite != nullptr) delete sprite;
    if (type == INTERACT_NPC) {
        sprite = new CharacterSprite(ti);
        centerSprite = false;
    } else {
        sprite = new Sprite(ti, w, h);
        centerSprite = true;
    }
    if (w <= 2) w = sprite->getWidth();
    if (h <= 2) h = sprite->getHeight();
}

void Entity::disposeSprite() {
    if (sprite != nullptr) delete sprite;
    sprite = nullptr;
}
