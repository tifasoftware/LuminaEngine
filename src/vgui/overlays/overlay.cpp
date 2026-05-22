#include "overlay.h"

Overlay::Overlay(Renderer *r, IControllable *p) {
    renderer = r;
    parent = p;

    completed = false;
    engaged = false;
}
