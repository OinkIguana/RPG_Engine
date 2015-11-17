#pragma once

#include "types.h"
#include "tile.h"

class Background {
public:
    Background() {}
    ~Background() {}
private:
    int layer;
    Rect pos;
};