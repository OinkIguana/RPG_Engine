#pragma once

#include <SDL.h>
#include "types.h"

class draw {
public:
    // Draw an entire texture at the given point
    static void texture(const Point& p, SDL_Texture* tex);
    // Draw part of the texture at the given point
    static void texture_part(const Point& p, SDL_Texture* tex, const Rect& src);
    // Draw a surface at the given point
    static void surface(const Point&, SDL_Surface*);
    // Clear the screen
    static void clear();
    // Present the image to the screen
    static void render();

    // Set the color for various things
    static void set_color(const Color&);
};