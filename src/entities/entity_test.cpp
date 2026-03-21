#include "entity.h"

void Entity::npcMoveTest() {
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

void Entity::npcTalkTest() {

}
