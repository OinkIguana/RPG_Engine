#pragma once
#include "actor.h"

class Player : public Actor {
public:
    Player() : Actor() {
        _sprite = Sprite::get("run_cat");
    }
    void step();
protected:
};