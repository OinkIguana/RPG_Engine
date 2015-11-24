#pragma once

#include "types.h"

class Image;

// A piece of a background
class Tile {
public:
    Tile(Image* img, const Rect& pos, const Rect& piece);
    Tile(Image* img, const Point& pos, const Rect& piece);
    ~Tile();

    void copy_to_surface(SDL_Surface* surf, const Point& off = { 0, 0 }) const;
    inline Rect pos() { return _pos; }
private:
    Rect _pos;
    Image* _img;
    Rect _piece;
    int _layer;
};