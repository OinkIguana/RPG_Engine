#include "rpg.h"

#define WINDOW_WIDTH    1024
#define WINDOW_HEIGHT   756

SDL_Window* RPG::_game_window;
SDL_Renderer* RPG::_game_renderer;
bool RPG::_done = false;
void RPG::init() {
    _game_window = SDL_CreateWindow("Untitled RPG", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    if (_game_window == NULL) {
        return;
    }
    _game_renderer = SDL_CreateRenderer(_game_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (_game_renderer == NULL) {
        return;
    }
}

void RPG::exit() {
    SDL_DestroyRenderer(_game_renderer);
    SDL_DestroyWindow(_game_window);
}

void RPG::process_events() {
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        switch (e.type) {
        case SDL_QUIT: 
            quit();
            break;
        }
    }
}
