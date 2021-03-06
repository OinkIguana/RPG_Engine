#include <iostream>
#include "rpg.h"
#include "all_actors.h"

void game();
void ev_step();
void ev_draw();

int main(int argc, char* argv[]) {
    //Initialize SDL
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        std::cout << "SDL_Init: " << SDL_GetError() << std::endl;
        return 1;
    }
    if (TTF_Init() != 0) {
        std::cout << "TTF_Init: " << TTF_GetError() << std::endl;
        SDL_Quit();
        return 2;
    }
    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        std::cout << "IMG_Init: " << IMG_GetError() << std::endl;
        TTF_Quit();
        SDL_Quit();
        return 3;
    }
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) { 
        std::cout << "Mix_OpenAudio: " << Mix_GetError() << std::endl;
        IMG_Quit();
        TTF_Quit();
        SDL_Quit();
        return 4;
    }

    //Run the game until error or quit
    game();

    //Quit SDL
    Mix_Quit();
    IMG_Quit();
    TTF_Quit();
    SDL_Quit();
    return 0;
}

void game() {
    //Open the game window
    RPG::init();

    //Import resources
    Font::import("test.fonts");
    FormatString::import("test.format");
    Image::import("test.image");
    Audio::import("test.audio");
    Sprite::import("test.sprite");
    ItemType::import("test.items");
    Dialog::import("test.dialog");
    Stat::import("test.stats");
    Skill::import("test.skill");
    SkillTree::import("test.tree");
    Progress::import();
    Room::import();

    Room::get("demo_inside")->go_to();
    Actor::create<Player>()->pos(Point(192, 192));
    // Audio::music_play("music");

    //Do the game stuff
    while (!RPG::is_done()) {
        RPG::process_events();
        ev_step();
        draw::clear();
        ev_draw();
        draw::render();
    }

    RPG::exit();
}

//Things to run once per frame
void ev_step() {
    RPG::step();
}

//Redraw the screen
void ev_draw() {
    RPG::draw();
}