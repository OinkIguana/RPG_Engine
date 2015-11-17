#include "draw.h"
#include "rpg.h"
#include <iostream>

void draw::texture(const Point& p, SDL_Texture* tex) {
    int w, h;
    SDL_QueryTexture(tex, NULL, NULL, &w, &h);
    SDL_Rect dest = Rect(0, 0, w, h) >> p;
    SDL_RenderCopy(RPG::game_renderer(), tex, NULL, &dest);
}
void draw::texture_part(const Point& p, SDL_Texture* tex, const Rect& src) {
    SDL_Rect dest = Rect(p.x, p.y, src.w, src.h);
    SDL_Rect _src = src;
    SDL_RenderCopy(RPG::game_renderer(), tex, &_src, &dest);
}
void draw::surface(const Point& p, SDL_Surface* surf) {
    texture(p, SDL_CreateTextureFromSurface(RPG::game_renderer(), surf));
}
void draw::clear() {
    SDL_SetRenderDrawColor(RPG::game_renderer(), 0xFF, 0xFF, 0xFF, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(RPG::game_renderer());
}
void draw::render() {
    SDL_RenderPresent(RPG::game_renderer());
}

void draw::set_color(const Color& col) {
    SDL_SetRenderDrawColor(RPG::game_renderer(), col.r, col.g, col.b, col.a);
}