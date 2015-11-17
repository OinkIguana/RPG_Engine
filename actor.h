#pragma once

#include "types.h"
#include "sprite.h"

class Actor {
public:
    Actor() : _id(c_id++) { all_actors[_id] = this; }
    ~Actor() { all_actors.erase(_id); }

    inline static Actor* get(const unsigned int& i) { return all_actors[i]; }
    template<class T>
    static unsigned int count();

    virtual void key_down(SDL_KeyboardEvent) {};
    virtual void key_up(SDL_KeyboardEvent) {};
    virtual void key(SDL_KeyboardEvent) {};

protected:
    const unsigned int _id;
    Sprite* _sprite;
    unsigned int _frame;
    Pointf _pos;
    Rectf _bbox;
    int _depth;

    static std::map<unsigned int, Actor*> all_actors;
    static unsigned int c_id;
};

template<class T>
unsigned int Actor::count() {
    if (typeid(T) == typeid(Actor)) { return all_actors.size(); }
    unsigned int n = 0;
    for (auto i = all_actors.begin(); i != all_actors.end(); ++i) {
        if (dynamic_cast<T*>(i->second) != nullptr) { ++n; }
    }
    return n;
}
