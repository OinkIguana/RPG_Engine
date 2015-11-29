#include "actor.h"

std::map<unsigned int, Actor*> Actor::all_actors;
unsigned int Actor::c_id = 0;

Actor::Actor() : _id(c_id++) {
    all_actors[_id] = this;
}

void Actor::clear(const bool & persistent) {
    unsigned int n;
    Actor** a = all<Actor>(&n);
    for (unsigned int i = 0; i < n; i++) {
        if (persistent || !a[i]->persistent()) {
            destroy(a[i]);
        }
    }
    delete[] a;
}

Actor::~Actor() { all_actors.erase(_id); }

void Actor::draw() {
    if (_sprite != nullptr) {
        _sprite->draw(pos(), frame(), _depth);
    }
}
