#pragma once

#include "actor.h"
#include "stats.h"
#include "inventory.h"

/*
#Actor: Pickup placeholder 50 1
#Actor: Apple apple
*/

class Pickup : public Actor {
public:
    Pickup(const std::string& type, const unsigned int& level = 1, const StatList& stats = StatList()) : Actor(), _type(ItemType::get(type)), _level(level), _stats(stats) {}
    bool pick_up();
private:
    ItemType* _type;
    StatList _stats;
    unsigned int _level;
};

class Apple : public Pickup {
public:
    Apple() : Pickup("Apple") { _sprite = Sprite::get("apple"); }
};