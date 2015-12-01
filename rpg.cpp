#include "rpg.h"

RPG::ActorList RPG::_actors;

SDL_Window* RPG::_game_window;
SDL_Renderer* RPG::_game_renderer;
bool RPG::_done = false;
RPG::Keystate* RPG::_keys = nullptr;
RPG::Keystate* RPG::_mouse = nullptr;
Point RPG::_mouse_pos = Point(0, 0);
const Uint8* RPG::_sdl_keys = nullptr;
int RPG::_num_keys = 0;

void RPG::init() {
    _game_window = SDL_CreateWindow("Untitled RPG", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    if (_game_window == NULL) {
        return;
    }
    _game_renderer = SDL_CreateRenderer(_game_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (_game_renderer == NULL) {
        return;
    };
    _sdl_keys = SDL_GetKeyboardState(&_num_keys);
    
    _keys = new Keystate[_num_keys];
    for (int i = 0; i < _num_keys; i++) {
        _keys[i] = Keystate::RELEASED;
    }
    _mouse = new Keystate[5]{ Keystate::RELEASED };
}

void RPG::exit() {
    SDL_DestroyRenderer(_game_renderer);
    SDL_DestroyWindow(_game_window);
}

void RPG::process_events() {
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        switch (e.type) {
        case SDL_KEYDOWN:
            if (_keys[e.key.keysym.scancode] == Keystate::RELEASED) {
                _keys[e.key.keysym.scancode] = Keystate::PRESSED;
                _each_actor([e](Actor* act) { act->key_down(e.key.keysym.scancode); });
            }
            break;
        case SDL_KEYUP:
            if (_keys[e.key.keysym.scancode] == Keystate::PRESSED) {
                _keys[e.key.keysym.scancode] = Keystate::RELEASED;
                _each_actor([e](Actor* act) { act->key_up(e.key.keysym.scancode); });
            }
            break;
        case SDL_MOUSEBUTTONDOWN:
            if (_mouse[e.button.button] == Keystate::RELEASED) {
                _mouse_pos = Point(e.button.x, e.button.y);
                _mouse[e.button.button] = Keystate::PRESSED;
                _each_actor([e](Actor* act) { act->mouse_down(e.button.button); });
            }
            break;
        case SDL_MOUSEBUTTONUP:
            if (_mouse[e.button.button] == Keystate::PRESSED) {
                _mouse[e.button.button] = Keystate::RELEASED;
                _each_actor([e](Actor* act) { act->mouse_up(e.button.button); });
            }
            break;
        case SDL_MOUSEWHEEL:
            _each_actor([e](Actor* act) { act->mouse_wheel(Point(e.wheel.x, e.wheel.y)); });
            break;
        case SDL_QUIT: 
            quit();
            break;
        }
    }
}

void RPG::step() {
    // Update actor list
    delete[] _actors.list;
    _actors.list = Actor::all<Actor>(&_actors.length);

    // Run the step
    _each_actor([](Actor* act) { act->step(); });
}

void RPG::draw() {
    // Update actor list
    unsigned int count;
    Background** bgs = Background::get_room_bgs(&count);
    for (unsigned int i = 0; i < count; i++) {
        bgs[i]->draw(); 
    }
    delete[] bgs;
    if (Actor::do_destroy()) {
        delete[] _actors.list;
        _actors.list = Actor::all<Actor>(&_actors.length);
    }
    _each_actor([](Actor* act) { act->draw(); });

    // Dialog on top always
    if (Dialog::visible()) {
        Dialog::draw();
    }
}