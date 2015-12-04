#pragma once

#include "actor.h"
#include "actor_demo_wall.h"
#include "dialog.h"

/*
#Actor: NPC walk_cat 50
#Actor: HelloCat walk_cat 50
#Actor: ByeCat walk_cat 50
*/
class NPC : public Solid {
public:
    NPC() : Solid() {
        _sprite = Sprite::get("walk_cat");
        frame(5);
    }
    virtual void draw() override { Actor::draw(); }
    inline Dialog* dialog() const { return _dialog; }
protected:
    Dialog* _dialog;
};

class HelloCat : public NPC {
public:
    HelloCat() : NPC() { _dialog = Dialog::get("CatGreeting"); }
};

class ByeCat : public NPC {
public:
    ByeCat() : NPC() { _dialog = Dialog::get("CatGoodbye"); }
};