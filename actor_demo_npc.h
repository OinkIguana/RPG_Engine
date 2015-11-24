#pragma once

#include "actor.h"

/*
#Actor: NPC walk_cat
*/
class NPC : public Wall {
public:
    NPC() : Wall() {
        _sprite = Sprite::get("walk_cat");
        frame(5);
    }
};