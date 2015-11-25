#pragma once

#include "actor.h"

/*
#Actor: Wall wall 0
*/
class Wall : public Actor {
public:
    Wall() : Actor() {
        _sprite = Sprite::get("wall");
    }
    virtual void draw() {}
};