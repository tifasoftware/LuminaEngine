#include "entities/warppoint.h"

WarpPoint* WarpPoint::createWarpPoint(const char *newmap) {
    WarpPoint* ret = new WarpPoint();
    ret->setMapName(newmap);
    return ret;
}
