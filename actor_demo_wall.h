#pragma once

#include "actor.h"

/*
#Actor: Wall wall 100
*/
class Wall : public Actor {
public:
    Wall() : Actor() {
        _sprite = Sprite::get("wall");
    }
    virtual void draw() {}
};