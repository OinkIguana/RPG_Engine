#pragma once

#include "actor.h"

/*
#Actor: Wall wall 150
*/
class Wall : public Actor {
public:
    Wall() : Actor() {
        _sprite = Sprite::get("wall");
    }
    virtual void draw() {}
};