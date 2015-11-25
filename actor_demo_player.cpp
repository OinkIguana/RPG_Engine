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
        if (collides<Wall>(pos() + d)) {
            // Find which way has the issue
            if (collides<Wall>(pos() + Point(d.x, 0))) { d.x = 0; }
            if (collides<Wall>(pos() + Point(0, d.y))) { d.y = 0; }
            // If going directly at a corner, just pick one
            if (collides<Wall>(pos() + d)) { d.x = 0; }
        }
        move(d);
        if (d != Point(0, 0)) {
            const int image_offset = ((-(Angle(d) + 90_deg)).deg) / 45 * 3;
            inc_frame();
            frame(frame() % 3 + image_offset);
        }
    }
}