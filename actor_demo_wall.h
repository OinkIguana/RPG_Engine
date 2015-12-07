#pragma once

#include "actor.h"
#include "actor_demo_solid.h"

/*
#Actor: Wall placeholder 150
*/
class Wall : public Solid {
public:
    Wall() : Solid() {
        bbox(Rect(0, 0, 32, 32));
    }
    virtual void room_start() override {
        if (!_merged) {
            merge<Wall>();
            _merged = true;
        }
    }
    virtual void room_end() override { _merged = false; }
private:
    static bool _merged;
};

