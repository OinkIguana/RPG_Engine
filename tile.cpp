#include "tile.h"
#include "image.h"

Tile::Tile(Image* img, const Rect& pos, const Rect& piece) : _img(img), _pos(pos), _piece(piece) {}
Tile::Tile(Image* img, const Point& pos, const Rect& piece) : _img(img), _pos(piece >> pos), _piece(piece) {}
Tile::~Tile() {}

void Tile::copy_to_surface(SDL_Surface* surf, const Point& off) const {
    _img->copy_to_surface(surf, (SDL_Rect)_piece, (SDL_Rect)(_pos + off));
}