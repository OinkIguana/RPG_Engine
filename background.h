#ifndef __RPG_BACKGROUND_H__
#define __RPG_BACKGROUND_H__

#include "types.h"
#include "tile.h"
#include <sdl.h>

class Background {
public:
	Background() {}
	~Background() {}
private:
	int layer;
	Rect pos;
};

#endif