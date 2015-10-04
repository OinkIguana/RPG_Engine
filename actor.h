#ifndef __RPG_ACTOR_H__
#define __RPG_ACTOR_H__

#include "types.h"

class Actor {
public:
	Actor() {}
	~Actor() {}
private:
	Pointf pos;
	Rectf bbox;
	int depth;

};

#endif