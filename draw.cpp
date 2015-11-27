#include "draw.h"
#include "rpg.h"

draw::Carry* draw::_carry = new draw::Carry();
Color draw::_color = Color::hex(0x000000);

void draw::texture(const Rect& p, const int& depth, SDL_Texture* tex, const bool& temp) {
    int w, h;
    SDL_QueryTexture(tex, NULL, NULL, &w, &h);
    _carry = (*_carry)(p, depth, Rect(0, 0, w, h), tex, temp);
}
void draw::texture(const Point& p, const int& depth, SDL_Texture* tex, const bool& temp) {
    int w, h;
    SDL_QueryTexture(tex, NULL, NULL, &w, &h);
    _carry = (*_carry)(Rect(0, 0, w, h) >> p, depth, Rect(0, 0, w, h), tex, temp);
}
void draw::texture_part(const Point& p, const int& depth, SDL_Texture* tex, const Rect& src, const bool& temp) {
    _carry = (*_carry)(Rect(p.x, p.y, src.w, src.h), depth, src, tex, temp);
}
void draw::surface(const Point& p, const int& depth, SDL_Surface* surf) {
    texture(p, depth, SDL_CreateTextureFromSurface(RPG::game_renderer(), surf), true);
}
void draw::surface(const Rect& p, const int& depth, SDL_Surface* surf) {
    texture(p, depth, SDL_CreateTextureFromSurface(RPG::game_renderer(), surf), true);
}
void draw::clear() {
    set_color(Color::hex(0xFFFFFF));
    SDL_RenderClear(RPG::game_renderer());
}
void draw::render() {
    unsigned int size;
    Carry ** list = Carry::extract_all(_carry, size);
    
    for (unsigned int i = 0; i < size; i++) {
        SDL_Rect src = list[i]->_piece;
        SDL_Rect dest = list[i]->_pos;
        SDL_RenderCopy(RPG::game_renderer(), list[i]->_tex, &src, &dest);
        delete list[i];
    }

    SDL_RenderPresent(RPG::game_renderer());

    delete[] list;
}

void draw::rect(const Rect& rect, const int& depth) {
    SDL_Rect dest = (SDL_Rect)(rect >> Rect(0, 0, 0, 0));
    SDL_Surface* surf = SDL_CreateRGBSurface(0, rect.w, rect.h, 32, 0, 0, 0, 0);
    SDL_FillRect(surf, &dest, SDL_MapRGB(surf->format, _color.r, _color.g, _color.b));
    surface(rect, depth, surf);
    SDL_FreeSurface(surf);
}

void draw::set_color(const Color& col) {
    _color = col;
    SDL_SetRenderDrawColor(RPG::game_renderer(), col.r, col.g, col.b, col.a);
}

int draw::Carry::_size = 0;

draw::Carry* draw::Carry::operator()(const Rect& pos, const int& depth, const Rect& piece, SDL_Texture* tex, const bool& temp) {
    _pos = pos;
    _depth = depth;
    _tex = tex;
    _piece = piece;
    _temp = temp;
    Carry::_size++;
    return new Carry(this);
}

void draw::Carry::extract(Carry** list) {
    if (_size) {
        list[--_size] = _parent;
        _parent->extract(list);
    }
}

draw::Carry** draw::Carry::extract_all(Carry* first, unsigned int& size) {
    size = _size;
    Carry** list = new Carry*[size];
    first->extract(list);
    util::quicksort<Carry*>(list, size, [](Carry* a, Carry* b) { return a->_depth < b->_depth; });
    return list;
}