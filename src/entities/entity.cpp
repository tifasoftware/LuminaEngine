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
    returnEntity->orientation = def.orientation;
    returnEntity->initializeSprite(-1);
    returnEntity->calculateTriggerBounds();

    return returnEntity;
}

void Entity::calculateTriggerBounds() {
    switch (orientation) {
        case FACE_ALL:
            trigger_h = h * 2;
            trigger_w = w * 2;
            trigger_x = getLeftX() - w;
            trigger_y = getTopY() - h;
            break;
        case FACE_LEFT:
            trigger_h = h;
            trigger_w = w * 2;
            trigger_x = getLeftX() - w;
            trigger_y = getTopY();
            break;
        case FACE_RIGHT:
            trigger_h = h;
            trigger_w = w * 2;
            trigger_x = getLeftX();
            trigger_y = getTopY();
            break;
        case FACE_UP:
            trigger_h = h * 2;
            trigger_w = w;
            trigger_x = getLeftX();
            trigger_y = getTopY() - h;
            break;
        case FACE_DOWN:
            trigger_h = h * 2;
            trigger_w = w;
            trigger_x = getLeftX();
            trigger_y = getTopY();
            break;
        case FACE_UD:
            trigger_h = h * 3;
            trigger_w = w;
            trigger_x = getLeftX();
            trigger_y = getTopY() - h;
            break;
        case FACE_LR:
            trigger_h = h;
            trigger_w = w * 3;
            trigger_x = getLeftX() - w;
            trigger_y = getTopY();
            break;
        default:
            trigger_h = h;
            trigger_w = w;
            trigger_x = getLeftX();
            trigger_y = getTopY();
            break;
    }
}

bool Entity::isInTrigger(int charX, int charY) {
    if (charX > trigger_x && charX < (trigger_x + trigger_w) && charY > trigger_y && charY < (trigger_y + trigger_h)) return true;
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

#ifdef PLATFORM_OSX
    SDL_Rect rec = {trigger_x - screenOffsetX, trigger_y - screenOffsetY, trigger_w, trigger_h};

    SDL_SetRenderDrawBlendMode(r->getRenderer(), SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(r->getRenderer(), 0, 150, 255, 100);

    SDL_RenderFillRect(r->getRenderer(), &rec);

    SDL_SetRenderDrawBlendMode(r->getRenderer(), SDL_BLENDMODE_NONE);
#endif
}

void Entity::update() {
    if (sprite != nullptr) sprite->animate(FRAME_RATE, moveX, moveY);

    if (moveX != 0) {
        x += moveX;
        trigger_x += moveX;
    }

    if (moveY != 0) {
        y += moveY;
        trigger_y += moveY;
    }

    //NPC Movement Test
    //This would ideally be replaced with a lua script
    //npcMoveTest();
}

void Entity::interact() {

}

void Entity::initializeSprite(int ti) {
    if (sprite != nullptr) delete sprite;
    switch (type) {
        case INTERACT_NPC:
            sprite = new CharacterSprite(ti);
            w = sprite->getWidth();
            h = sprite->getHeight();
            centerSprite = false;
            break;
        case TRIGGER_BATTLEFIELD:
        case TRIGGER_LUA:
        case TRIGGER_WARP:
            sprite = nullptr;
            centerSprite = false;
            orientation = FACE_NONE;
            if (w <= 2) w = 16;
            if (h <= 2) h = 16;
            break;
        default:
            sprite = new Sprite(ti, w, h);
            centerSprite = true;
            if (w <= 2) w = 16;
            if (h <= 2) h = 16;
            break;
    }

}

void Entity::disposeSprite() {
    if (sprite != nullptr) delete sprite;
    sprite = nullptr;
}
