#pragma once
#include "actor.h"

class Room;

/*
#Actor: Door wall 150 1
*/

class Door : public Actor {
public:
    Door(const std::string& room);
    void enter();
    inline Room* room() const { return _room; }
    virtual void draw() {}
private:
    Room* _room = nullptr;
};