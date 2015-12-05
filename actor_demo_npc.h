#pragma once

#include "actor.h"
#include "actor_demo_player.h"
#include "actor_demo_wall.h"
#include "progress.h"
#include "dialog.h"

/*
#Actor: NPC walk_cat 50
#Actor: HelloCat sit_cat 50
#Actor: ByeCat sit_cat 50
#Actor: QuestCat sit_cat 50
*/
class NPC : public Solid {
public:
    NPC() : Solid() { _sprite = Sprite::get("sit_cat"); }
    virtual void draw() override { Actor::draw(); }
    inline Dialog* dialog() const { return _dialog; }
    void talk() {
        _on_talk();
        Dialog::set(_dialog);
    }
protected:
    virtual void _on_talk() {};
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

class QuestCat : public NPC {
public:
    QuestCat() : NPC() { _dialog = Dialog::get("CatQuest.before"); }
    virtual void _on_talk() override;
};