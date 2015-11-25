#pragma once

#include "actor.h"

/*
#Actor: NPC walk_cat 50
*/
class NPC : public Wall {
public:
    NPC() : Wall() {
        _sprite = Sprite::get("walk_cat");
        frame(5);
    }
    virtual void draw() { Actor::draw(); }
};