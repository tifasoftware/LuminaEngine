#include "collision_convert.h"

CollisionType convertFromString(char str[])
{
    if (strcmp(str, "NORTH") == 0) return NORTH;
    if (strcmp(str, "SOUTH") == 0) return SOUTH;
    if (strcmp(str, "EAST") == 0) return EAST;
    if (strcmp(str, "WEST") == 0) return WEST;
    if (strcmp(str, "NEO") == 0) return NEO;
    if (strcmp(str, "SEO") == 0) return SEO;
    if (strcmp(str, "NWO") == 0) return NWO;
    if (strcmp(str, "SWO") == 0) return SWO;
    if (strcmp(str, "NEI") == 0) return NEI;
    if (strcmp(str, "SEI") == 0) return SEI;
    if (strcmp(str, "NWI") == 0) return NWI;
    if (strcmp(str, "SWI") == 0) return SWI;

    return NONE;
}