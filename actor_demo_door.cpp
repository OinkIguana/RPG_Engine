#include "actor_demo_door.h"
#include "room.h"
bool Door::_merged = false;

Door::Door(const std::string & room) : Actor(), _room(Room::get(room)) { 
    bbox(Rect(0, 0, 32, 32));
}

void Door::enter() { _room->go_to(); }