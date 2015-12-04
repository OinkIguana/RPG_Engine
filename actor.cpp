#include "actor.h"

std::map<unsigned int, Actor*> Actor::all_actors;
std::vector<Actor*> Actor::to_destroy;
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

bool Actor::do_destroy() {
    if (to_destroy.size() == 0) { return false; }
    while (to_destroy.size() > 0) {
        delete to_destroy.back();
        to_destroy.pop_back();
    }
    return true;
}

Actor::~Actor() { all_actors.erase(_id); }

void Actor::draw() {
    if (_sprite != nullptr) {
        _sprite->draw(pos(), frame(), _depth);
    }
}
