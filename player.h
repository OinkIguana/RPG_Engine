#pragma once
#include "actor.h"

class Player : public Actor {

protected:
    Sprite* _sprite = Sprite::get("white_cat");

};