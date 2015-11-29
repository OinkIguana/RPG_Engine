#include "room.h"

#include "room_demo_inside.cpp"
#include "room_demo_outside.cpp"

void Room::import() {
    Room::add_room(new RM_demo_inside());
    Room::add_room(new RM_demo_outside());
}
