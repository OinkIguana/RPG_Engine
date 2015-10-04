#ifndef __RPG_SPRITE_H
#define __RPG_SPRITE_H

#include "types.h"
#include "image.h"

class Sprite {
public:
	Sprite() {}
	~Sprite() {}
private:
	Image image;
	Point origin;
	Rect* frames;
	Rect stretch;
};

#endif