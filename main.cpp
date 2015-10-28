#include <iostream>
#include "engine.h"
#include "stats.h"
#include "inventory.h"
#include "dialog.h"

void game();

int main(int argc, char* argv[]) {
    //Initialize SDL 
    SDL_Init(SDL_INIT_EVERYTHING);

    //Run the game until error or quit
    game();

    //Quit SDL 
    SDL_Quit();

	return 0;
}

void game() {
    //Open the game window
    SDL_Window* game_window = SDL_CreateWindow("Untitled RPG", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1024, 756, SDL_WINDOW_SHOWN);
    if (game_window == NULL) {
        return;
    }
    SDL_Surface* game_surface = SDL_GetWindowSurface(game_window);

    //Import resources
    Font::import("test.fonts");
    Stat::import("test.stats");
    ItemType::import("test.items");
    FormatString::import("test.format");
    Dialog::import("main.dialog");
    
    //Do some stuff
    FormatString str =  "Hello #gworld,``` how are you today %"_format;
 
    Message msg =       "Cameron %\%"_speaker +
                        "Hello there\~ How are #gyou?"_message;

    Message msg2 = Message("Pearl", "Hello! I am #rgood\~ How about you?");
    std::cout << str.to_string() << "\n";

    std::cout << msg.to_string() << "\n";

    std::cout << msg2.to_string() << "\n";
}