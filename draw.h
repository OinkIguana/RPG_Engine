#pragma once

#include <SDL.h>
#include "types.h"

class draw {
public:
    static void texture(const Point&, SDL_Texture*);
    static void texture_part(const Point&, SDL_Texture*, const Rect&);
    static void surface(const Point&, SDL_Surface*);
    static void clear();
    static void render();

    static void set_color(const Color&);
private:
};