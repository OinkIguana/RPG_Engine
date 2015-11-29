#pragma once

#include "actor.h"

/* 
#Actor: Player walk_cat 50
*/
class Player : public Actor {
public:
    Player();
    virtual void key_down(const SDL_Scancode&);
    virtual void step();
private:
    Sequence<unsigned int> _frame_sequence = Sequence<unsigned int>(16, 0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 2, 2, 1, 1, 1, 1);
};