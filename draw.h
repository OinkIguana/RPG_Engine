#pragma once

#include <SDL.h>
#include "types.h"

class draw {
public:
    // Draw an entire texture stretched to fill a given space
    static void texture(const Rect& p, SDL_Texture* tex);
    // Draw an entire texture at the given point
    static void texture(const Point& p, SDL_Texture* tex);
    // Draw part of the texture at the given point
    static void texture_part(const Point& p, SDL_Texture* tex, const Rect& src);
    // Draw a surface at the given point
    static void surface(const Point& p, SDL_Surface* surf);
    // Clear the screen
    static void clear();
    // Present the image to the screen
    static void render();

    // Draw a rectangle
    static void rect(const Rect& rect);

    // Set the color for various things
    static void set_color(const Color&);
};