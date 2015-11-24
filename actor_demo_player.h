#pragma once

#include "actor.h"

/* 
#Actor: Player walk_cat
*/
class Player : public Actor {
public:
    Player() : Actor() {
        _sprite = Sprite::get("walk_cat");
    }
    virtual void key_down(const SDL_Scancode&);
    virtual void step();
};