#pragma once

#include "actor.h"

/*
#Actor: Wall wall
*/
class Wall : public Actor {
public:
    Wall() : Actor() {
        _sprite = Sprite::get("wall");
    }
};