#include "actor_demo_player.h"
#include "rpg.h"

void Player::key_down(const SDL_Scancode& key) {
    if (key == SDL_SCANCODE_Z) {
        if (!Dialog::visible()) {
            if (against<NPC>()) {
                Dialog::set(Dialog::get("CatGreeting"));
            }
        } else {
            Dialog::next();
        }
    }
}

void Player::step() {
    if (!Dialog::visible()) {
        Point d = Point(RPG::key(SDL_SCANCODE_RIGHT) - RPG::key(SDL_SCANCODE_LEFT), RPG::key(SDL_SCANCODE_DOWN) - RPG::key(SDL_SCANCODE_UP)) * 4;
        if (collides<Wall>(pos() + Point(d.x, 0))) { d.x = 0; }
        if (collides<Wall>(pos() + Point(0, d.y))) { d.y = 0; }
        move(d);

    }
}