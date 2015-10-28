#ifndef __RPG_SPRITE_H
#define __RPG_SPRITE_H

#include <map>
#include <string>
#include "types.h"
#include "image.h"

class Sprite {
public:
    static Sprite* get(std::string) { return new Sprite(); }

	~Sprite() {}
private:
    Sprite() {}

    std::string name;
	Image image;
	Point origin;
	Rect* frames;
	Rect stretch;

    static const std::map<std::string, Sprite*> all_sprites;
};

#endif