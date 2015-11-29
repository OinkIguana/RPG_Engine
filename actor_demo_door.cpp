#include "actor_demo_door.h"
#include "room.h"

Door::Door(const std::string & room) : Actor(), _room(Room::get(room)) { _sprite = Sprite::get("wall"); }

void Door::enter() { _room->go_to(); }