#pragma once

#include "actor.h"
#include "inventory.h"
#include "actor_demo_pickup.h"

/* 
#Actor: Player walk_cat 50
*/
class Player : public Actor {
public:
    Player();
    virtual void key_down(const SDL_Scancode&);
    virtual void step();

    inline static Inventory& inventory() { return _inventory; }
private:
    Sequence<unsigned int> _frame_sequence = Sequence<unsigned int>(16, 0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 2, 2, 1, 1, 1, 1);
    static Inventory _inventory;
};