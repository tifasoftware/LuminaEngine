#include "entity.h"
#include "trigger.h"

bool Trigger::isInTrigger(int charX, int charY) {
    if (charX > x && charX < (x + w) && charY > y && charY < (y + h)) return true;
    return false;
}