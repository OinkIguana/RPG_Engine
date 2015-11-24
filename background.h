#pragma once

#include <sdl.h>
#include <map>
#include <functional>
#include "config.h"
#include "draw.h"
#include "types.h"
#include "tile.h"

// A background, created from a set of tiles
class Background {
public:
    static Background* get(const std::string& name, Image* img = nullptr, const Point& p = { 0, 0 }, const int& depth = 0);
    // Create a new temporary background from a set of tiles
    Background(const int& n, Tile ** tiles, const int& depth);
    ~Background();

    // Destroys all temporary backgrounds
    static void clear_temp();

    // Gets all temporary backgrounds. count gets filled with the number of backgrounds
    static Background** get_temps(unsigned int* count);

    // Draws the background to the screen
    void draw() const;

    inline bool visible() { return _visible; }
    inline void toggle() { _visible = !_visible; }
    inline void hide() { _visible = false; }
    inline void show() { _visible = true; }

    // Merges the backgrounds into one, destroying the old and returning only the new one
    Background flatten(const unsigned int& n, Background** bgs) {}
private:
    // Create a new reusable background from an image
    Background(const std::string& name, Image* img, const Point& p, const int& depth);
    std::string _name = "temp";
    bool _visible = true;
    int _depth;
    Rect _pos;
    Image* _img;

    static std::map<Image*, Background*> temp_backgrounds;
    static std::map<std::string, Background*> all_backgrounds;
};
