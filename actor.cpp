#include "actor.h"

std::map<unsigned int, Actor*> Actor::all_actors;
unsigned int Actor::c_id = 0;

Actor::Actor() : _id(c_id++) {
    all_actors[_id] = this;
}

Actor::~Actor() { all_actors.erase(_id); }

void Actor::draw() {
    if (_sprite != nullptr) {
        _sprite->draw(pos(), frame());
    }
}
