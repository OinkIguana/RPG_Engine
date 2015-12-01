#include "actor_demo_pickup.h"
#include "actor_demo_player.h" 

bool Pickup::pick_up() {
    return Player::inventory().add(_type, 1, _level, _stats) == 0;
}
