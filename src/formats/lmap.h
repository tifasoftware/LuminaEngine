#include <stdint.h>
struct LMAPHeader 
{
    char magic[4];
    uint16_t version;
    uint16_t width;
    uint16_t height;
    char tileset[64];
    uint16_t tiles[64 * 64];
};