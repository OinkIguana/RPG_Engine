#pragma once

#include <sdl.h>

#if SDL_BYTEORDER == SDL_BIG_ENDIAN
#define RMASK   0xff000000
#define GMASK   0x00ff0000
#define BMASK   0x0000ff00
#define AMASK   0x000000ff
#else
#define RMASK   0x000000ff
#define GMASK   0x0000ff00
#define BMASK   0x00ff0000
#define AMASK   0xff000000
#endif

#define WINDOW_WIDTH    1024
#define WINDOW_HEIGHT   768

#define GUI_LAYER               1000
#define DEFAULT_ACTOR_LAYER     50

#if _WIN32 || _WIN64
#if _WIN64
#define ENVIRONMENT64
#else
#define ENVIRONMENT32
#endif
#endif
#if __GNUC__
#if __x86_64__ || __ppc64__
#define ENVIRONMENT64
#else
#define ENVIRONMENT32
#endif
#endif