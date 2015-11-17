#pragma once

#include <functional>
#include "types.h"
#include "sprite.h"

class Actor {
public:
    Actor();
    ~Actor();

    // Returns the number of Actor's of type T that currently exist
    template<class T>
    static unsigned int count();
    // Get an array of pointers to all Actors of type T.
    // count is set to the length of the array
    template<class T>
    static T** all(unsigned int* count = nullptr);

    // Get an actor by its id
    inline static Actor* get(const unsigned int& id) { return all_actors[id]; }

    // Create a new Actor of type T
    // Returns the pointer to the new Actor
    template<class T>
    inline static T* create() { return new T(); }

    virtual void key_down(SDL_KeyboardEvent) {};
    virtual void key_up(SDL_KeyboardEvent) {};
    virtual void key(SDL_KeyboardEvent) {};

    // Run once per frame
    virtual void step() {};
    // Run once per frame, after the screen has been cleared
    virtual void draw();
protected:
    Sprite* _sprite;

    // Get the current frame of the Sprite this Actor is on
    inline unsigned int frame() const { return _frame; }
    // Set the current frame of the Sprite this Actor is on. Returns the new frame number
    inline unsigned int frame(const unsigned int& d) { return _frame = d % _sprite->frames(); }
    // Increment the current frame by a given amount. Returns the new frame number
    inline unsigned int inc_frame(const int& d) { return _frame = (_frame + d + _sprite->frames()) % _sprite->frames(); }

    // Get the current position of the Actor
    inline Point pos() const { return _pos; }
    // Set the current position of the Actor. Returns the new position
    inline Point pos(const Point& d) { return _pos = d; }
    // Shift the current position of the Actor by a given amount. Returns the new position
    inline Point move(const Point& d) { return _pos += d; }

    // Get the current drawing depth of the Actor
    inline int depth() const { return _depth; }
    // Set the current drawing depth of the Actor
    inline int depth(const int& d) { return _depth = d; }

    // Get the id of the Actor
    inline unsigned int id() const { return _id; }
private:
    const unsigned int _id;
    unsigned int _frame = 0;
    Point _pos;
    int _depth = 0;

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

template<class T>
T** Actor::all(unsigned int* count) {
    auto i = all_actors.begin();
    T** list;
    unsigned int n = 0;

    std::function<void(void)> next;
    (next = [&] {
        if (i == all_actors.end()) {
            list = new Actor*[n];
            if (count != nullptr) {
                *count = n;
            }
            return;
        }
        T* is = nullptr;
        if ((is = dynamic_cast<T*>(i->second)) != nullptr) {
            n++;
        }
        ++i;
        next();
        if (is != nullptr) {
            list[--n] = is;
        }
    })();
    return list;
}
