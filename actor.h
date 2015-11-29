#pragma once

#include "types.h"
#include "sprite.h"
#include "config.h"

/*
    Base for an Actor
    For use with the room editor, an Actor must have this line in the file somewhere:
    #Actor: name image [depth [args]]
*/
class Actor {
public:
    Actor();

    // Returns the number of Actor's of type T that currently exist
    template<typename T>
    static unsigned int count();
    // Get an array of pointers to all Actors of type T.
    // count is set to the length of the array
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

    // Destroys the given Actor
    inline static void destroy(Actor* p) { delete p; }

    virtual void key_down(const SDL_Scancode& key) {};
    virtual void key_up(const SDL_Scancode& key) {};
    virtual void mouse_down(const Uint8& button) {};
    virtual void mouse_up(const Uint8& button) {};
    virtual void mouse_wheel(const Point& dist) {};

    // NOT IMPLEMENTED
    virtual void controller_down(const SDL_JoystickID& id, const Uint8& button) {};
    // NOT IMPLEMENTED
    virtual void controller_up(const SDL_JoystickID& id, const Uint8& button) {};

    // Run once per frame
    virtual void step() {};
    // Run once per frame, after the screen has been cleared
    virtual void draw();

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
    inline Rect bbox() const { return (Rect)_pos << (_sprite != nullptr ? _sprite->frame(_frame) : Rect::no_box); }

    // Get the current drawing depth of the Actor
    inline int depth() const { return _depth; }
    // Set the current drawing depth of the Actor
    inline int depth(const int& d) { return _depth = d; }

    // Get the persistence of the Actor (for room end)
    inline bool persistent() const { return _persistent; }

    // Get the id of the Actor
    inline unsigned int id() const { return _id; }
protected:
    ~Actor();
    Sprite* _sprite = nullptr;
    bool _persistent = false;

    // Determines if the current Actor collides with another
    inline bool collides(Actor* o) const { return (bbox() & o->bbox()) != Rect::no_box; }
    // Determines if the current Actor would collide with another at a given position
    inline bool collides(Actor* o, const Point& p) const { return ((bbox() >> p) & o->bbox()) != Rect::no_box; }
    // Determines if the current Actor collides with any of the others
    inline bool collides(Actor** o, const unsigned int& n) const { for (unsigned int i = 0; i < n; i++) { if(collides(o[i])) return true; } return false; }
    // Determines if the current Actor would collide with any of the others at a given position
    inline bool collides(Actor** o, const unsigned int& n, const Point& p) const { for (unsigned int i = 0; i < n; i++) { if (collides(o[i], p)) return true; } return false; }
    // Determines if the current Actor collides with any of a type
    template<typename T>
    inline bool collides() const;
    // Determines if the current Actor would collide with any of a type at a given position
    template<typename T>
    inline bool collides(const Point& p) const;

    // Determines which others the current Actor collides with of a type
    template<typename T>
    inline T ** collides(unsigned int* count) const;
    // Determines which others the current Actor would collide with of a type at a given position
    template<typename T>
    inline T ** collides(const Point& p, unsigned int* count) const;

    // Determines if the current Actor lies against another
    inline bool against(Actor* o) const { return    (((bbox().rs() == o->bbox().x) || (bbox().x == o->bbox().rs())) && (bbox().bot() > o->bbox().y && bbox().y < o->bbox().bot())) ||
                                                    (((bbox().bot() == o->bbox().y) || (bbox().y == o->bbox().bot())) && (bbox().rs() > o->bbox().x && bbox().x < o->bbox().rs())); }
    // Determines if the current Actor would lie against another at a given position
    inline bool against(Actor* o, const Point& p) const { return ((bbox() >> p).rs() == o->bbox().x) || ((bbox() >> p).bot() == o->bbox().y) || ((bbox() >> p).x == o->bbox().rs()) || ((bbox() >> p).y == o->bbox().bot()); }
    // Determines if the current Actor lies against any of the others
    inline bool against(Actor** o, const unsigned int& n) const { for (unsigned int i = 0; i < n; i++) { if (against(o[i])) return true; } return false; }
    // Determines if the current Actor would lie against any of the others at a given position
    inline bool against(Actor** o, const unsigned int& n, const Point& p) const { for (unsigned int i = 0; i < n; i++) { if (against(o[i], p)) return true; } return false; }
    // Determines if the current Actor lies against any of a type
    template<typename T>
    inline bool against() const;
    // Determines if the current Actor lies against any of a type at a given position
    template<typename T>
    inline bool against(const Point& p) const;

    // Determines which Actors the current Actor lies against of a type
    template<typename T>
    inline T ** against(unsigned int* count = nullptr) const;
    // Determines which Actors the current Actor lies against of a type at a given position
    template<typename T>
    inline T ** against(const Point& p, unsigned int* count = nullptr) const;
private:
    const unsigned int _id;
    unsigned int _frame = 0;
    Point _pos;
    int _depth = DEFAULT_ACTOR_LAYER;

    static std::map<unsigned int, Actor*> all_actors;
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

template<typename T>
inline bool Actor::collides() const {
    unsigned int* n = new unsigned int();
    Actor** a = (Actor**)all<T>(n);
    bool does = collides(a, *n);
    delete n;
    delete[] a;
    return does;
}

template<typename T>
inline bool Actor::collides(const Point& p) const {
    unsigned int* n = new unsigned int;
    Actor** a = (Actor**)all<T>(n);
    bool does = collides(a, *n, p);
    delete n;
    delete[] a;
    return does;
}

template<typename T>
inline bool Actor::against() const {
    unsigned int* n = new unsigned int();
    Actor** a = (Actor**)all<T>(n);
    bool does = against(a, *n);
    delete n;
    delete[] a;
    return does;
}

template<typename T>
inline bool Actor::against(const Point& p) const {
    unsigned int* n = new unsigned int();
    Actor** a = (Actor**)all<T>(n);
    bool does = against(a, *n, p);
    delete n;
    delete[] a;
    return does;
}

template<typename T>
inline T ** Actor::against(unsigned int* count) const {
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
inline T ** Actor::against(const Point & p, unsigned int* count) const {
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
inline T ** Actor::collides(unsigned int* count) const {
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
inline T ** Actor::collides(const Point & p, unsigned int* count) const {
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

#include "all_actors.h"