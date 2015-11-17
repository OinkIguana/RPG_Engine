#pragma once

#include "types.h"
#include "image.h"

class Tile {
public:
    Tile() {}
    ~Tile() {}
private:
    Point pos;
    // Image image;
    Rect piece;
    int layer;
};