#pragma once

#ifdef PLATFORM_PS2

#include <ps2_all_drivers.h>

static void _reset_IOP(void) {
    SifInitRpc(0);
    while (!SifIopReset(NULL, 0)) {};
    while (!SifIopSync()) {};
    SifInitRpc(0);
    sbv_patch_enable_lmb();
    sbv_patch_disable_prefix_check();
}

#endif