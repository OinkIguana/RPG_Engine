#ifndef __RPG_TILE_H__
#define __RPG_TILE_H__

#include "types.h"
#include "image.h"

class Tile {
public:
	Tile() {}
	~Tile() {}
private:
	Point pos;
	Image image;
	Rect piece;
	int layer;
};

#endif