#include "room.h"

std::map<std::string, Room*> Room::all_rooms = std::map<std::string, Room*>();
Room* Room::_current_room = nullptr;
Room* Room::_previous_room = nullptr;

Room * Room::get(const std::string& name) {
    auto old = all_rooms.find(name);
    if (old != all_rooms.end()) {
        return old->second;
    } else {
        return nullptr;
    }
}

Room::~Room() {
    all_rooms.erase(_name);
}

void Room::go_to() {
    if (_current_room != nullptr) {
        _current_room->end();
        _previous_room = _current_room;
    }
    _current_room = this;
    start();
}

void Room::start() {
    tiles();
    actors();
    on_room_start();
}

void Room::end() {
    on_room_end();
    Actor::clear();
    Background::remove_room_bgs();
}