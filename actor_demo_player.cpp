#include "actor_demo_player.h"
#include "rpg.h"

Inventory Player::_inventory = Inventory(8);

Player::Player() : Actor() {
    _sprite = Sprite::get("walk_cat");
    _persistent = true;
}

void Player::key_down(const SDL_Scancode& key) {
    if (key == SDL_SCANCODE_Z) {
        if (!Dialog::visible()) {
            unsigned int n;
            NPC ** npcs = against<NPC>(&n);
            if (n >= 1) {
                npcs[0]->talk();
            }
            delete[] npcs;
        }
    }
}

void Player::step() {
    if (!Dialog::visible()) {
        Point d = Point(RPG::key(SDL_SCANCODE_RIGHT) - RPG::key(SDL_SCANCODE_LEFT), RPG::key(SDL_SCANCODE_DOWN) - RPG::key(SDL_SCANCODE_UP)) * 4;
        if (collides<Solid>(pos() + d)) {
            // Find which way has the issue
            if (collides<Solid>(pos() + Point(d.x, 0))) { d.x = 0; }
            if (collides<Solid>(pos() + Point(0, d.y))) { d.y = 0; }
            // If going directly at a corner, just pick one
            if (collides<Solid>(pos() + d)) { d.x = 0; }
        }
        move(d);
        if (d != Point(0, 0)) {
            const int image_offset = ((-(Angle(d) + 90_deg)).deg) / 45 * 3;
            frame((++_frame_sequence) + image_offset);
            Door * door = collides<Door>();
            if (door) {
                door->enter();
                unsigned int n;
                Door** doors = all<Door>(&n);
                for (unsigned int i = 0; i < n; i++) {
                    if (doors[i]->room() == Room::previous_room()) {
                        pos(doors[i]->pos() + (d * 8));
                        break;
                    }
                }
                delete[] doors;
            }
        }

        Pickup * item = collides<Pickup>(pos());
        if (item) {
            if (item->pick_up()) {
                Actor::destroy(item);
            }
        }
    }
}