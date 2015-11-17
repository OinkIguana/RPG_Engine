#pragma once

#include <SDL.h>
#include <SDL_TTF.h>
#include "actor.h"
//#include "background.h"
#include "dialog.h"
#include "draw.h"
#include "font.h"
#include "formatstring.h"
#include "image.h"
#include "inventory.h"
#include "sprite.h"
#include "stats.h"
//#include "tile.h"
#include "types.h"

class RPG {
public:
    RPG() {}
    ~RPG() {}

    static void init();
    static void exit();

    inline static SDL_Window* game_window() { return _game_window; }
    inline static SDL_Renderer* game_renderer() { return _game_renderer; }

    inline static void quit() { _done = true; }
    inline static bool is_done() { return _done; }

    static void process_events();
    static void step();
    static void draw();
private:
    static SDL_Window* _game_window;
    static SDL_Renderer* _game_renderer;
    static bool _done;
};