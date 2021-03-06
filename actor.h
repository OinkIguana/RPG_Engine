#pragma once

#include <map>
#include <vector>
#include "types.h"
#include "sprite.h"
#include "config.h"

/*
    Base for an Actor
    For use with the room editor, an Actor must have this line in the file somewhere:
    #Actor: name image [depth [arg_count]]
*/
class Actor {
public:
    Actor();

    // Returns the number of Actor's of type T that currently exist
    template<typename T>
    static unsigned int count();
    // Get an array of pointers to all Actors of type T.
    // count is set to the length of the array
    // Calls new[], so delete[] when finished
    template<typename T>
    static T** all(unsigned int* count = nullptr);

    // Get an actor by its id
    inline static Actor* get(const unsigned int& id) { return all_actors[id]; }
    // Delete all actors
    static void clear(const bool& persistent = false);

    // Create a new Actor of type T
    // Returns the pointer to the new Actor
    template<typename T>
    inline static T* create() { return new T(); }
    template<typename T>
    inline static T* create(const std::string& arg) { return new T(arg); }

    // Queues the given actor for destruction
    inline static void destroy(Actor* p) { to_destroy.push_back(p); }
    // Destroys all actors in the queue. Returns true if there were objects destroyed
    static bool do_destroy();

    // Input events
    virtual void key_down(const SDL_Scancode& key) {}
    virtual void key_up(const SDL_Scancode& key) {}
    virtual void mouse_down(const Uint8& button) {}
    virtual void mouse_up(const Uint8& button) {}
    virtual void mouse_wheel(const Point& dist) {}

    // NOT IMPLEMENTED
    virtual void controller_down(const SDL_JoystickID& id, const Uint8& button) {}
    // NOT IMPLEMENTED
    virtual void controller_up(const SDL_JoystickID& id, const Uint8& button) {}

    // Run once per frame
    virtual void step() {}
    // Run once per frame, after the screen has been cleared
    virtual void draw();

    // Run once at the beginning of the room
    virtual void room_start() {}
    // Run once at the end of the room
    virtual void room_end() {}

    // Get the current frame of the Sprite this Actor is on
    inline unsigned int frame() const { return _frame; }
    // Set the current frame of the Sprite this Actor is on. Returns the new frame number
    inline unsigned int frame(const unsigned int& d) { return _frame = d % _sprite->frames(); }
    // Increment the current frame by a given amount. Returns the new frame number
    inline unsigned int inc_frame(const int& d = 1) { return _frame = (_frame + d + _sprite->frames()) % _sprite->frames(); }

    // Get the current position of the Actor
    inline Point pos() const { return _pos; }
    // Set the current position of the Actor. Returns the new position
    inline Point pos(const Point& d) { return _pos = d; }
    // Shift the current position of the Actor by a given amount. Returns the new position
    inline Point move(const Point& d) { return _pos += d; }

    // Get the bounding box
    inline Rect bbox() const { return _bbox == Rect::no_box ? (_sprite != nullptr ? _sprite->frame(_frame) >> _pos : Rect::no_box) : _bbox >> (_pos + _bbox); }
    // Set the bounding box (override sprite)
    inline Rect bbox(const Rect& b) { return _bbox = b; }

    // Get the current drawing depth of the Actor
    inline int depth() const { return _depth; }
    // Set the current drawing depth of the Actor
    inline int depth(const int& d) { return _depth = d; }

    // Get the persistence of the Actor (for room end)
    inline bool persistent() const { return _persistent; }

    // Get the id of the Actor
    inline unsigned int id() const { return _id; }

    operator bool() { return this != nullptr; }
protected:
    ~Actor();
    Sprite* _sprite = nullptr;
    bool _persistent = false;

    // Determines if the current Actor collides with another
    inline bool collides(Actor* o) const { return (bbox() & o->bbox()) != Rect::no_box; }
    // Determines if the current Actor would collide with another at a given position
    inline bool collides(Actor* o, const Point& p) const { return ((bbox() >> p) & o->bbox()) != Rect::no_box; }
    // Determines if the current Actor collides with any of the others
    inline Actor* collides(Actor** o, const unsigned int& n) const { for (unsigned int i = 0; i < n; i++) { if(collides(o[i])) return o[i]; } return nullptr; }
    // Determines if the current Actor would collide with any of the others at a given position
    inline Actor* collides(Actor** o, const unsigned int& n, const Point& p) const { for (unsigned int i = 0; i < n; i++) { if (collides(o[i], p)) return o[i]; } return nullptr; }
    // Determines if the current Actor collides with any of a type
    template<typename T>
    T* collides() const;
    // Determines if the current Actor would collide with any of a type at a given position
    template<typename T>
    T* collides(const Point& p) const;

    // Determines which others the current Actor collides with of a type
    // Calls new[], so delete[] when finished
    template<typename T>
    inline T ** collides(unsigned int* count) const;
    // Determines which others the current Actor would collide with of a type at a given position
    // Calls new[], so delete[] when finished
    template<typename T>
    inline T ** collides(const Point& p, unsigned int* count) const;

    // Determines if the current Actor lies against another
    inline bool against(Actor* o) const { return bbox().against(o->bbox()); }
    // Determines if the current Actor would lie against another at a given position
    bool against(Actor* o, const Point& p) const { return ((bbox() >> p).rs() == o->bbox().x) || ((bbox() >> p).bot() == o->bbox().y) || ((bbox() >> p).x == o->bbox().rs()) || ((bbox() >> p).y == o->bbox().bot()); }
    // Determines if the current Actor lies against any of the others
    inline Actor* against(Actor** o, const unsigned int& n) const { for (unsigned int i = 0; i < n; i++) { if (against(o[i])) return o[i]; } return nullptr; }
    // Determines if the current Actor would lie against any of the others at a given position
    inline Actor* against(Actor** o, const unsigned int& n, const Point& p) const { for (unsigned int i = 0; i < n; i++) { if (against(o[i], p)) return o[i]; } return nullptr; }
    // Determines if the current Actor lies against any of a type
    template<typename T>
    T* against() const;
    // Determines if the current Actor lies against any of a type at a given position
    template<typename T>
    T* against(const Point& p) const;

    // Determines which Actors the current Actor lies against of a type
    // Calls new[], so delete[] when finished
    template<typename T>
    T ** against(unsigned int* count) const;
    // Determines which Actors the current Actor lies against of a type at a given position
    // Calls new[], so delete[] when finished
    template<typename T>
    T ** against(const Point& p, unsigned int* count = nullptr) const;

    // Merges adjacent objects (by bbox) into one larger one (speeds up collision)
    template<typename T>
    static void merge();
private:
    const unsigned int _id;
    unsigned int _frame = 0;
    Point _pos;
    Rect _bbox = Rect::no_box;
    int _depth = DEFAULT_ACTOR_LAYER;

    static std::map<unsigned int, Actor*> all_actors;
    static std::vector<Actor*> to_destroy;
    static unsigned int c_id;
};

template<typename T>
unsigned int Actor::count() {
    if (typeid(T) == typeid(Actor)) { return all_actors.size(); }
    unsigned int n = 0;
    for (auto i = all_actors.begin(); i != all_actors.end(); ++i) {
        if (dynamic_cast<T*>(i->second) != nullptr) { ++n; }
    }
    return n;
}

template<typename T>
T** Actor::all(unsigned int* count) {
    auto i = all_actors.begin();
    T** list;
    unsigned int n = 0;

    std::function<void(void)> next;
    (next = [&] {
        if (i == all_actors.end()) {
            list = new T*[n];
            if (count != nullptr) {
                *count = n;
            }
            return;
        }
        T* is = nullptr;
        if ((is = dynamic_cast<T*>(i->second)) != nullptr) {
            for (unsigned int j = 0; j < to_destroy.size(); j++) {
                if (to_destroy[j] == is) {
                    is = nullptr;
                }
            }
            if (is != nullptr) {
                n++;
            }
        }
        ++i;
        next();
        if (is != nullptr) {
            list[--n] = is;
        }
    })();
    return list;
}

template<typename T>
T* Actor::collides() const {
    unsigned int n;
    T ** a = all<T>(&n);
    T* does = dynamic_cast<T*>(collides((Actor**)a, n));
    delete[] a;
    return does;
}

template<typename T>
T* Actor::collides(const Point& p) const {
    unsigned int n;
    T ** a = all<T>(&n);
    T* does = dynamic_cast<T*>(collides((Actor**)a, n, p));
    delete[] a;
    return does;
}

template<typename T>
T*  Actor::against() const {
    unsigned int n;
    T ** a = all<T>(&n);
    T* does = dynamic_cast<T*>(against((Actor**)a, n));
    delete[] a;
    return does;
}

template<typename T>
inline T* Actor::against(const Point& p) const {
    unsigned int n;
    T ** a = all<T>(&n);
    T* does = dynamic_cast<T*>(against((Actor**)a, n, p));
    delete[] a;
    return does;
}

template<typename T>
T ** Actor::against(unsigned int* count) const {
    auto i = all_actors.begin();
    T** list;
    unsigned int n = 0;
    std::function<void(void)> next;
    (next = [&] {
        if (i == all_actors.end()) {
            list = new T*[n];
            if (count != nullptr) {
                *count = n;
            }
            return;
        }
        T* is = nullptr;
        if ((is = dynamic_cast<T*>(i->second)) != nullptr) {
            if (against(is)) {
                n++;
            } else {
                is = nullptr;
            }
        }
        ++i;
        next();
        if (is != nullptr) {
            list[--n] = is;
        }
    })();
    return list;
}

template<typename T>
T ** Actor::against(const Point & p, unsigned int* count) const {
    auto i = all_actors.begin();
    T** list;
    unsigned int n = 0;
    std::function<void(void)> next;
    (next = [&] {
        if (i == all_actors.end()) {
            list = new T*[n];
            if (count != nullptr) {
                *count = n;
            }
            return;
        }
        T* is = nullptr;
        if ((is = dynamic_cast<T*>(i->second)) != nullptr) {
            if (against(is, p)) {
                n++;
            } else {
                is = nullptr;
            }
        }
        ++i;
        next();
        if (is != nullptr) {
            list[--n] = is;
        }
    })();
    return list;
}

template<typename T>
T ** Actor::collides(unsigned int* count) const {
    auto i = all_actors.begin();
    T** list;
    unsigned int n = 0;
    std::function<void(void)> next;
    (next = [&] {
        if (i == all_actors.end()) {
            list = new T*[n];
            if (count != nullptr) {
                *count = n;
            }
            return;
        }
        T* is = nullptr;
        if ((is = dynamic_cast<T*>(i->second)) != nullptr) {
            if (collides(is)) {
                n++;
            } else {
                is = nullptr;
            }
        }
        ++i;
        next();
        if (is != nullptr) {
            list[--n] = is;
        }
    })();
    return list;
}

template<typename T>
T ** Actor::collides(const Point & p, unsigned int* count) const {
    auto i = all_actors.begin();
    T** list;
    unsigned int n = 0;
    std::function<void(void)> next;
    (next = [&] {
        if (i == all_actors.end()) {
            list = new T*[n];
            if (count != nullptr) {
                *count = n;
            }
            return;
        }
        T* is = nullptr;
        if ((is = dynamic_cast<T*>(i->second)) != nullptr) {
            if (collides(is, p)) {
                n++;
            } else {
                is = nullptr;
            }
        }
        ++i;
        next();
        if (is != nullptr) {
            list[--n] = is;
        }
    })();
    return list;
}

template<typename T>
void Actor::merge() {
    unsigned int n = 1;
    T ** act = all<T>(&n);
    {   // Horizontal
        unsigned int i = 0;
        while (i < n) {
            Rect total = act[i]->bbox();
            for (unsigned int j = i + 1; j < n; j++) {
                Rect comb = total | act[j]->bbox();
                if (comb.w - total.w <= act[j]->bbox().w && total.h == act[j]->bbox().h && total.h == comb.h) {
                    total = comb;
                    destroy(act[j]);
                }
            }
            act[i]->pos(total);
            act[i]->bbox(total >> Point(0, 0));
            unsigned int x = n;
            delete[] act;
            act = all<T>(&n);
            if (n == x) { i++; }
        }
    }
    {   // Vertical
        unsigned int i = 0;
        while (i < n) {
            Rect total = act[i]->bbox();
            for (unsigned int j = i + 1; j < n; j++) {
                Rect comb = total | act[j]->bbox();
                if (comb.h - total.h <= act[j]->bbox().h && total.w == act[j]->bbox().w && total.w == comb.w) {
                    total = comb;
                    destroy(act[j]);
                }
            }
            act[i]->pos(total);
            act[i]->bbox(total >> Point(0, 0));
            unsigned int x = n;
            delete[] act;
            act = all<T>(&n);
            if (n == x) { i++; }
        }
    }
    delete[] act;
}