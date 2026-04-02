#pragma once
#include "platform.h"

#ifdef LIB_SDL2
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_gamecontroller.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_log.h>
#endif

#ifdef LIB_SDL1
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>

#include <platform/sdl2_compat/SDL_Renderer.h>
#include <platform/sdl2_compat/SDL_Texture.h>
#include <platform/sdl2_compat/SDL_Window.h>
#include <platform/sdl2_compat/SDL_misc.h>
#include <platform/sdl2_compat/SDL_events.h>
#endif
