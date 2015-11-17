#include <iostream>
#include "rpg.h"

#include "player.h"
#include "npc.h"

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
        SDL_Quit();
        return 3;
    }

    //Run the game until error or quit
    game();

    //Quit SDL
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
    Sprite::import("test.sprite");
    ItemType::import("test.items");
    Dialog::import("main.dialog");
    Stat::import("test.stats");

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
void ev_step() {}

//Redraw the screen
void ev_draw() {}