#include "draw.h"
#include "rpg.h"

draw::Carry* draw::_carry = new draw::Carry();
Color draw::_color = Color::hex(0x000000);
void draw::texture(const Rect& p, const int& depth, SDL_Texture* tex) {
    int w, h;
    SDL_QueryTexture(tex, NULL, NULL, &w, &h);
    _carry = (*_carry)(p, depth, Rect(0, 0, w, h), tex);
}
void draw::texture(const Point& p, const int& depth, SDL_Texture* tex) {
    int w, h;
    SDL_QueryTexture(tex, NULL, NULL, &w, &h);
    _carry = (*_carry)(Rect(0, 0, w, h) >> p, depth, Rect(0, 0, w, h), tex);
}
void draw::texture_part(const Point& p, const int& depth, SDL_Texture* tex, const Rect& src) {
    _carry = (*_carry)(Rect(p.x, p.y, src.w, src.h), depth, src, tex);
}
void draw::surface(const Point& p, const int& depth, SDL_Surface* surf) {
    texture(p, depth, SDL_CreateTextureFromSurface(RPG::game_renderer(), surf));
}
void draw::clear() {
    SDL_SetRenderDrawColor(RPG::game_renderer(), 0xFF, 0xFF, 0xFF, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(RPG::game_renderer());
}
void draw::render() {
    unsigned int size;
    Carry** list = Carry::extract_all(_carry, size);
    
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
    SDL_Texture* tex = SDL_CreateTextureFromSurface(RPG::game_renderer(), surf);
    SDL_FreeSurface(surf);
    _carry = (*_carry)(rect, depth, rect >> Rect(0, 0, 0, 0), tex, true);
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
    draw::Carry::_size++;
    return new draw::Carry(this);
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
    {
        std::function<void(Carry*[], const unsigned int)> qs;
        (qs = [&qs](Carry* part[] , const unsigned int len) -> void {
            Carry ** left = new Carry*[len - 1];
            Carry ** right = new Carry*[len - 1];
            unsigned int il = 0, ir = 0;
            Carry* pivot = part[len - 1];
            for (unsigned int i = 0; i < len - 1; i++) {
                if (*part[i] < *pivot) {
                    left[il++] = part[i];
                } else {
                    right[ir++] = part[i];
                }
            }
            if (il > 1) { qs(left, il); }
            if (ir > 1) { qs(right, ir); }
            for (unsigned int i = 0; i < len; i++) {
                if (i < il) {
                    part[i] = left[i];
                } else if (i == il) {
                    part[i] = pivot;
                } else {
                    part[i] = right[i - il - 1];
                }
            }
        })(list, size);
    }
    return list;
}