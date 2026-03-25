#pragma once

#include <graphics/Renderer.h>
#include <graphics/Texture.h>
#include <graphics/effects/fade.h>
#include <entities/TileMap.h>
#include <entities/character.h>
#include <entities/entity.h>
#include <common/types.h>
#include <common/utils.h>
#include <common/vector.h>
#include <sound/soundsystem.h>
#include <vgui/text.h>
#include <vgui/panel.h>
#include <vgui/UIElement.h>
#include <vgui/button.h>
#include <vgui/dialogue.h>
#include <game/gameplay.h>
#include <game/controller.h>
#include <game/gameplay_state.h>
#include <game/IControllable.h>
#include <platform/platform.h>

extern "C"{
    #include <lua.h>
    #include <lualib.h>
    #include <lauxlib.h>
}

#ifdef PLATFORM_OSX
#include <mach-o/dyld.h>
#endif